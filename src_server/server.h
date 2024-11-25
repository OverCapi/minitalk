/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:06:51 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 23:09:12 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_H
# define SERVER_H

# include <sys/types.h>
# include <signal.h>
# include <unistd.h>

# include "../utils/utils.h"
# include "../ft_printf/ft_printf.h"

# define ERROR_MALLOC "Error\nAllocation error\n"
# define ERROR_SIGNAL "Error\nSignal error\n"

typedef struct s_sig_buffer
{
	int	*buffer;
	int	current_sig;
	int	size;
}	t_sig_buffer;

#endif