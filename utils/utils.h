/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:17:35 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/26 14:53:45 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../ft_printf/ft_printf.h"
# include "stdlib.h"

size_t	ft_strlen(const char *str);
int		ft_atoi_safe(const char *nptr);
void	exit_msg(const char *msg, int exit_status);
void	*ft_memset(void	*s, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

#endif