/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:44 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/26 16:20:55 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int g_recever = 0;

// static void	send_byte(int server_pid, char byte)
// {
// 	int			bit_index;
// 	u_int8_t	mask;

// 	mask = 0b10000000;
// 	bit_index = 0;
// 	while (++bit_index <= 8)
// 	{
// 		if ((byte & mask) >> (7 - bit_index + 1) == 0)
// 		{
// 			if (kill(server_pid, SIGUSR1) == -1)
// 				exit_msg(ERROR_SIGNAL, 1);
// 		}
// 		else
// 		{
// 			if (kill(server_pid, SIGUSR2) == -1)
// 				exit_msg(ERROR_SIGNAL, 1);
// 		}
// 		usleep(100);
// 		mask = mask >> 1;
// 	}
// }

// static void	send_message(int server_pid, const char *msg)
// {
// 	int			i;

// 	i = -1;
// 	while (msg[++i])
// 		send_byte(server_pid, msg[i]);
// 	send_byte(server_pid, msg[i]);
// }

static void	handler(int sig)
{
	// ft_printf("Signal received %d\n", sig == SIGUSR2);
	if (sig == SIGUSR1)
		exit_msg(CONFIRM_MSG, 0);
	else
		g_recever = 1;
}

static void	init_action(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(sigaction));
	action.sa_handler = &handler;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
}

// t : 116 : 0111 0100
//   		 1000 0000
void	send_bit(int server_pid, char byte, int bit_index)
{
	u_int8_t mask;

	mask = 0b10000000 >> bit_index;
	if (((byte & mask) >> (7 - bit_index)) == 0)
	{
		// ft_printf("Sending 0\n");
		if (kill(server_pid, SIGUSR1) == -1)
			exit_msg(ERROR_SIGNAL, 1);
	}
	else
	{
		// ft_printf("Sending 1\n");
		if (kill(server_pid, SIGUSR2) == -1)
			exit_msg(ERROR_SIGNAL, 1);
	}
	g_recever = 0;
}

int	main(int argc, char **argv)
{
	unsigned int	server_pid;
	char			*msg;
	int				bit_index;
	size_t			i;

	i = 0;
	init_action();
	bit_index = 1;
	if (argc != 3)
		exit_msg(ERROR_USAGE, 1);
	server_pid = ft_atoi_safe(argv[1]);
	msg = argv[2];
	send_bit(server_pid, msg[i], 0);
	while (1)
	{
		if (g_recever == 1)
		{
			ft_printf("Sending %c\n", msg[i]);
			if (i < ft_strlen(msg) + 1)
			{
				send_bit(server_pid, msg[i], bit_index);
				bit_index++;
				if (bit_index == 8)
				{
					bit_index = 0;
					i++;
				}
			}
		}
		pause();
	}
	return (0);
}
