/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:42 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/26 19:37:06 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "server.h"

void	exit_error(const char *error_msg)
{
	ft_printf("%s", error_msg);
	exit(1);
}

char	*add_to_buffer(char *buffer, char byte)
{
	char		*new_buffer;
	static int	allocation_size = 256;
	static int	len = 1;

	if (!buffer)
	{
		allocation_size = 256;
		len = 1;
		buffer = (char *)malloc(allocation_size * sizeof(char));
		if (!buffer)
			exit_error(ERROR_MALLOC);
	}
	else if (len == allocation_size)
	{
		allocation_size *= 2;
		new_buffer = (char *)malloc(allocation_size * sizeof(char));
		if (!new_buffer)
		{
			free(buffer);
			exit_error(ERROR_MALLOC);
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

void	handler(int sig, siginfo_t *info, void *context)
{
	static char	*buffer = NULL;
	static char	byte = 0;
	static int	bit_index = 0;

	(void)context;
	if (sig == SIGUSR1)
		byte = (byte << 1) | 0;
	else
		byte = (byte << 1) | 1;
	bit_index++;
	if (bit_index == 8)
	{
		if (byte == 0)
		{
			if (buffer)
				ft_printf("%s", buffer);
			free(buffer);
			buffer = NULL;
			if (info && kill(info->si_pid, SIGUSR1) == -1)
				exit_error(ERROR_SIGNAL);
		}
		else
			buffer = add_to_buffer(buffer, byte);
		byte = 0;
		bit_index = 0;
	}
}

void	init_action(void)
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
