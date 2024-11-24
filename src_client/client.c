/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:44 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/24 15:25:41 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	print_error(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	return (1);
}

// 0101 0101
// 0101 0101 & 0000 0001 = 0000 0001
int	send_byte(int server_pid, char c)
{
	size_t		i;
	u_int8_t	mask;

	i = 0;
	mask = 0b00000001;
	while (i < 8)
	{
		if ((c & mask) >> i == 0)
		{
			ft_printf("0");
			kill(server_pid, SIGUSR1);
		}
		else
		{
			ft_printf("1");
			kill(server_pid, SIGUSR2);
		}
		mask = mask << 1;
		i++;
	}
	ft_printf("\n");
	return (0);
}

int	send_message(int server_pid, char *message)
{
	size_t	i;

	i = 0;
	while (message[i])
	{
		ft_printf("send byte : %c\n", message[i]);
		send_byte(server_pid, message[i]);
		i++;
	}
	ft_printf("send byte : %c\n", message[i]);
	send_byte(server_pid, message[i]);
	return (0);
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*message;

	(void)argv;
	if (argc != 3)
		return (print_error(ERROR_USAGE));
	else
	{
		server_pid = ft_atoi_safe(argv[1]);
		if (server_pid < 2)
			return (print_error(ERROR_PID));
		message = argv[2];
		send_message(server_pid, message);
	}
	return (0);
}