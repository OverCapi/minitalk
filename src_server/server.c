/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:42 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 16:47:51 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

#include <stdio.h>

void	exit_prog(const char *error_message)
{
	write(2, error_message, ft_strlen(error_message));
	exit(1);
}

void	add_to_buffer(char byte)
{
	static char		*buffer;
	char			*new_buffer;
	size_t			len_newbuffer;

	if (!buffer)
	{
		buffer = (char *)malloc(1);
		if (!buffer)
			exit_prog(ERROR_MALLOC);
		buffer[0] = '\0';
	}
	if (!byte)
	{
		ft_printf("%s", buffer);
		free(buffer);
		buffer = NULL;
		return ;
	}
	len_newbuffer = ft_strlen(buffer) + 1;
	new_buffer = (char *)malloc((len_newbuffer + 1) * sizeof(char));
	ft_strlcpy(new_buffer, buffer, len_newbuffer + 1);
	free(buffer);
	buffer = new_buffer;
	buffer[len_newbuffer - 1] = (char)byte;
	buffer[len_newbuffer] = '\0';
}

void	send_confirm_message(unsigned int client_pid)
{
	kill(client_pid, SIGUSR1);
}

void	sig_handler(int sig_num)
{
	static unsigned int	client_pid;
	static char			byte;
	static size_t		bit_num;

	if (sig_num == SIGUSR1 || sig_num == SIGUSR2)
	{
		if (bit_num	<= sizeof(unsigned int) * 8)
		{
			if (sig_num == SIGUSR1)
				client_pid = (client_pid << 1) | 0;
			else
				client_pid = (client_pid << 1) | 1;
		}
		if (bit_num	== (sizeof(unsigned int) * 8))
			ft_printf("PID receive !, pid : %u\n", (client_pid));
		else if (sig_num == SIGUSR1)
			byte = (byte << 1) | 0;
		else
			byte = (byte << 1) | 1;
		bit_num++;
	}
	ft_printf("bit_num : %d\n", (int)bit_num);
	if (bit_num > sizeof(unsigned int) * 8 && (bit_num - sizeof(unsigned int) * 8) == 8)
	{
		add_to_buffer(byte);
		if (byte == 0)
			send_confirm_message(client_pid);
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