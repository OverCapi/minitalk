/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 19:17:35 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 19:55:24 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "stdlib.h"

size_t	ft_strlen(const char *str);
int		ft_atoi_safe(const char *nptr);
void	*ft_memset(void	*s, int c, size_t n);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_realloc(void *ptr, size_t size, size_t new_size);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);

# endif