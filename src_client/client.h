/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:07:12 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 18:54:00 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../utils/utils.h"
# include "../ft_printf/ft_printf.h"

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>

# define TIMEOUT 100000 // 10 seconds

# define ERROR_USAGE "Error\nUsage: ./client <server_pid> <message>\n"
# define ERROR_PID "Error\nInvalid PID\n"
# define ERROR_TIMEOUT "Error\nConfirmation message too long to receive\n"

#endif