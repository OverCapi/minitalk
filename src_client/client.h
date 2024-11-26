/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:07:12 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 23:31:21 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_H
# define CLIENT_H

# include "../utils/utils.h"
# include "../ft_printf/ft_printf.h"

# include <unistd.h>
# include <sys/types.h>
# include <signal.h>

# define CONFIRM_MSG "Message succefully received\n"

# define ERROR_USAGE "Error\nUsage: ./client <server_pid> <message>\n"
# define ERROR_PID "Error\nInvalid PID\n"
# define ERROR_SIGNAL "Error\nSignal error\n"

#endif