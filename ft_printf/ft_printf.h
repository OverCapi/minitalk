/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 09:26:50 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/24 14:20:33 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

/*	UTILS FUNCTION */
size_t	ft_strlen_pf(const char *str);
char	*ft_strchr_pf(const char *s, int c);
void	ft_putchar_fd_pf(char c, int fd);
void	ft_putstr_fd_pf(char *s, int fd);
void	ft_putnbr_fd_pf(int n, int fd);

/* CONVERTER UTILS */
int		get_dec_size(unsigned int nb, int sign);
void	ft_putunbr(unsigned int nbr);
int		get_hex_size(size_t nb);
void	ft_puthexa(size_t nb, int maj);

/* CONVERTER */
int		char_converter(unsigned char c);
int		str_converter(char *str);
int		ptr_converter(size_t addr);
int		dec_converter(unsigned int nb, int sign);
int		hex_converter(unsigned int nb, int maj);

int		ft_printf(const char *format, ...);

#endif