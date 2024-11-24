/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:17:35 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/24 15:18:56 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "stdlib.h"

size_t	ft_strlen(const char *str);
int		ft_atoi_safe(const char *nptr);
void	*ft_memset(void	*s, int c, size_t n);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

# endif