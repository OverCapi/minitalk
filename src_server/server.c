/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:42 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/26 20:06:00 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

static char	*init_buffer(int *allocation_size, int *len)
{
	char	*buffer;

	*allocation_size = 256;
	*len = 1;
	buffer = (char *)malloc(*allocation_size * sizeof(char));
	if (!buffer)
		exit_msg(ERROR_MALLOC, 1);
	buffer[0] = '\0';
	return (buffer);
}

static char	*add_to_buffer(char *buffer, char byte)
{
	char		*new_buffer;
	static int	allocation_size = 256;
	static int	len = 1;

	if (!buffer)
		buffer = init_buffer(&allocation_size, &len);
	else if (len == allocation_size)
	{
		allocation_size *= 2;
		new_buffer = (char *)malloc(allocation_size * sizeof(char));
		if (!new_buffer)
		{
			free(buffer);
			exit_msg(ERROR_MALLOC, 1);
		}
		ft_strlcpy(new_buffer, buffer, len + 2);
		free(buffer);
		buffer = new_buffer;
	}
	buffer[len - 1] = byte;
	buffer[len] = '\0';
	len += 1;
	return (buffer);
}

static void	handler(int sig, siginfo_t *info, void *context)
{
	static char	*buffer = NULL;
	static char	byte = 0;
	static int	bit_index = 0;

	(void)context;
	if (sig == SIGUSR1)
		byte = (byte << 1) | 0;
	else
		byte = (byte << 1) | 1;
	if (++bit_index == 8)
	{
		if (byte == 0)
		{
			if (buffer)
				ft_printf("%s", buffer);
			free(buffer);
			buffer = NULL;
			if (info && kill(info->si_pid, SIGUSR1) == -1)
				exit_msg(ERROR_SIGNAL, 1);
		}
		else
			buffer = add_to_buffer(buffer, byte);
		byte = 0;
		bit_index = 0;
	}
}

static void	init_action(void)
{
	struct sigaction	action;

	ft_memset(&action, 0, sizeof(sigaction));
	action.sa_sigaction = &handler;
	action.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
}

int	main(void)
{
	int					server_pid;

	init_action();
	server_pid = getpid();
	ft_printf("Server PID : %d\n", server_pid);
	while (1)
		continue ;
}
