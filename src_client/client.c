/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 17:05:44 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/23 19:27:47 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client.h"

static int	print_error(char *error_msg)
{
	write(2, error_msg, ft_strlen(error_msg));
	return (1);
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 3)
		return (print_error(ERROR_USAGE));
	return (0);
}