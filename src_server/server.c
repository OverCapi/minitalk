/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:42 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 20:10:50 by llemmel          ###   ########.fr       */
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
	buffer = NULL;
	buffer = new_buffer;
	buffer[len_newbuffer - 1] = (char)byte;
	buffer[len_newbuffer] = '\0';
}

void	add_sig(t_sig_buffer *sig, int sig_num)
{
	size_t	size;

	size = sig->size * sizeof(int);
	sig->buffer = (int *)ft_realloc(sig->buffer, size, size + sizeof(int));
	sig->size += 1;
	if (sig_num == SIGUSR1)
		sig->buffer[size] = 0;
	else
		sig->buffer[size] = 1;
}

void	*remove_sig(t_sig_buffer *sig)
{
	size_t	size;
	int		*new_buffer;

	size = sig->size * sizeof(int);
	new_buffer = (int *)malloc(size - sizeof(int));
	if (!new_buffer)
		return (NULL);
	ft_memset(new_buffer, 0, size - sizeof(int));
	ft_memcpy(new_buffer, sig->buffer + 1, size - sizeof(int));
}

void	sig_handler(int sig_num)
{
	static t_sig_buffer sig_buffer;

	if (!sig_buffer.buffer)
	{
		sig_buffer.buffer = (int *)malloc(sizeof(int));
		if (!sig_buffer.buffer)
			exit_prog(ERROR_MALLOC);
		ft_memset(&sig_buffer, 0, sizeof(sig_buffer));
	}
	add_sig(&sig_buffer, sig_num);
}

void	sig_handler(int sig_num)
{
	static unsigned int	client_pid;
	static char			byte;
	static size_t		bit_num;
	size_t				size;

	size = sizeof(unsigned int) * 8;
	if (sig_num == SIGUSR1 || sig_num == SIGUSR2)
	{
		if (bit_num	< size)
		{
			if (sig_num == SIGUSR1)
				client_pid = (client_pid << 1) | 0;
			else
				client_pid = (client_pid << 1) | 1;
		}
		else if (sig_num == SIGUSR1)
			byte = (byte << 1) | 0;
		else
			byte = (byte << 1) | 1;
		bit_num++;
	}
	if (bit_num > size && (bit_num - size) == 8)
	{
		// ft_printf("client pid : %u\n", client_pid);
		add_to_buffer(byte);
		bit_num = size;
		if (byte == 0)
		{
			kill(client_pid, SIGUSR1);
			usleep(100);
			client_pid = 0;
			bit_num = 0;
		}
		byte = 0;
	}
	usleep(100);
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
	{
		usleep(100);
		continue ;
	}
	return (0);
}