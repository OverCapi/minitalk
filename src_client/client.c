/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:44 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/26 00:04:37 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

volatile sig_atomic_t	g_received;

void	exit_prog(const char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	exit(1);
}

int	send_byte(unsigned int server_pid, char c, int bit_num)
{
	u_int8_t	mask;

	mask = 0x80 >> bit_num;
	if ((c & mask) >> (7 - bit_num) == 0)
		kill(server_pid, SIGUSR1);
	else
		kill(server_pid, SIGUSR2);
	g_received = 0;
	usleep(100);
	return (0);
}

int	send_pid(unsigned int server_pid)
{
	size_t			i;
	size_t			size;
	u_int32_t		mask;
	unsigned int	client_pid;

	i = 1;
	client_pid = getpid();
	ft_printf("Client PID: %u\n", client_pid);
	mask = 0x80000000;
	size = sizeof(unsigned int) * 8;
	while (i <= size)
	{
		if ((client_pid & mask) >> (size - i) == 0)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				exit_prog(ERROR_SIGNAL);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				exit_prog(ERROR_SIGNAL);
		}
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
	else if (sig_num == SIGUSR2)
		g_received = 1;
}

void	set_sig_action(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}

int	main(int argc, char **argv)
{
	unsigned int		server_pid;
	char				*message;
	int					i;
	int					bit_num;

	if (argc != 3)
		exit_prog(ERROR_USAGE);
	server_pid = ft_atoi_safe(argv[1]);
	if (server_pid < 2)
		exit_prog(ERROR_PID);
	i = 0;
	g_received = 0;
	message = argv[2];
	set_sig_action();
	send_pid(server_pid);
	ft_printf("server_pid: %u\n", server_pid);
	while (1)
	{
		if (g_received == 1)
		{
			send_byte(server_pid, message[i], bit_num);
			bit_num++;
			if (bit_num == 8)
			{
				bit_num = 0;
				i++;
			}
		}
		usleep(100);
		continue ;
	}
	return (0);
}
