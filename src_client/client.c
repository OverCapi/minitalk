/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:44 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 19:15:52 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	print_error(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	return (1);
}

int	send_byte(int server_pid, char c)
{
	size_t		i;
	u_int8_t	mask;

	i = 1;
	mask = 0b10000000;
	while (i <= 8)
	{
		if ((c & mask) >> (8 - i) == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		mask = mask >> 1;
		i++;
	}
	return (0);
}

int	send_message(unsigned int server_pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		send_byte(server_pid, message[i]);
		usleep(100);
		i++;
	}
	send_byte(server_pid, message[i]);
	usleep(100);
	return (0);
}

int	send_pid(unsigned int server_pid, unsigned int client_pid)
{
	size_t		i;
	size_t		size;
	u_int32_t	mask;

	i = 1;
	mask = 0x80000000;
	size = sizeof(unsigned int) * 8;
	while (i <= size)
	{
		if ((client_pid & mask) >> (size - i) == 0)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(100);
		mask = mask >> 1;
		i++;
	}
	return (0);
}

void	sig_handler(int sig_num)
{
	if (sig_num == SIGUSR1)
	{
		ft_printf("Successfully received messages");
		exit(0);
	}
}

void	set_sig_action(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGUSR1, &act, NULL);
}

int	main(int argc, char **argv)
{
	unsigned int		server_pid;
	unsigned int		client_pid;
	char				*message;
	int					i;

	if (argc != 3)
		return (print_error(ERROR_USAGE));
	else
	{
		i = 0;
		client_pid = getpid();
		// ft_printf("client pid : %u\n", client_pid);
		server_pid = ft_atoi_safe(argv[1]);
		if (server_pid < 2)
			return (print_error(ERROR_PID));
		message = argv[2];
		set_sig_action();
		send_pid(server_pid, client_pid);
		send_message(server_pid, message);
		while (i < TIMEOUT)
		{
			i++;
			usleep(1000);
			continue ;
		}
		return (print_error(ERROR_TIMEOUT));
	}
	return (0);
}