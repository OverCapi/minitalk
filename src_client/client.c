/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:44 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/27 13:19:34 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static void	send_byte(int server_pid, char byte)
{
	int			bit_index;
	u_int8_t	mask;

	mask = 0b10000000;
	bit_index = 0;
	while (++bit_index <= 8)
	{
		if ((byte & mask) >> (7 - bit_index + 1) == 0)
		{
			if (kill(server_pid, SIGUSR1) == -1)
				exit_msg(ERROR_SIGNAL, 1);
		}
		else
		{
			if (kill(server_pid, SIGUSR2) == -1)
				exit_msg(ERROR_SIGNAL, 1);
		}
		usleep(TIME);
		mask = mask >> 1;
	}
}

static void	send_message(int server_pid, const char *msg)
{
	int	i;

	i = -1;
	while (msg[++i])
		send_byte(server_pid, msg[i]);
	send_byte(server_pid, msg[i]);
}

static void	handler(int sig)
{
	if (sig == SIGUSR1)
		exit_msg(CONFIRM_MSG, 0);
}

static void	init_action(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(sigaction));
	action.sa_handler = &handler;
	sigaction(SIGUSR1, &action, NULL);
}

int	main(int argc, char **argv)
{
	unsigned int	server_pid;
	char			*msg;

	if (argc != 3)
		exit_msg(ERROR_USAGE, 1);
	server_pid = ft_atoi_safe(argv[1]);
	msg = argv[2];
	init_action();
	send_message(server_pid, msg);
	while (1)
		continue ;
	return (0);
}
