/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llemmel <llemmel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 19:51:58 by llemmel           #+#    #+#             */
/*   Updated: 2024/11/25 20:09:02 by llemmel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_realloc(void *ptr, size_t size, size_t new_size)
{
	void	*dest;

	if (!ptr)
		return (NULL);
	dest = (void *)malloc(new_size);
	if (!dest)
		return (NULL);
	ft_memset(dest, 0, new_size);
	ft_memcpy(dest, ptr, size);
	free(ptr);
	ptr = NULL;
	return (dest);
}
