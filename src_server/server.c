/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:42 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/24 15:28:46 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	exit_prog(const char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	exit(1);
}

void	add_to_buffer(u_int8_t byte)
{
	static char		*buffer;
	char			*new_buffer;
	size_t			len_buffer;

	if (!buffer)
	{
		buffer = (char *)malloc(1);
		if (!buffer)
			exit_prog(ERROR_MALLOC);
	}
	len_buffer = ft_strlen(buffer);
	new_buffer = (char *)malloc((len_buffer + 1) * sizeof(char));
	ft_strlcpy(new_buffer, buffer, len_buffer + 1);
	free(buffer);
	buffer = new_buffer;
	buffer[len_buffer - 1] = (char)byte;
	if (byte == 0)
	{
		ft_printf("%s", buffer);
		free(buffer);
		buffer = NULL;
	}
}

void	sig_handler(int sig_num)
{
	static u_int8_t	byte;
	static size_t	bit_num;

	if (sig_num == SIGUSR1 || sig_num == SIGUSR2)
	{
		if (sig_num == SIGUSR1)
		{
			ft_printf("0");
			byte = (byte << 1);
		}
		else if (sig_num == SIGUSR2)
		{
			ft_printf("1");
			byte = (byte << 1) | 1;
		}
		bit_num++;
	}
	if (bit_num == 8)
	{
		ft_printf("byte receive : (%c)\n", byte);
		add_to_buffer(byte);
		byte = 0;
		bit_num = 0;
	}
}

void	set_sig_action(void)
{
	struct sigaction	act;

	ft_memset(&act, 0, sizeof(act));
	act.sa_handler = &sig_handler;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
}
int	main(void)
{
	unsigned int		server_pid;

	server_pid = getpid();
	ft_printf("PID : %u\n", server_pid);
	set_sig_action();
	while (1)
		continue ;
	return (0);
}