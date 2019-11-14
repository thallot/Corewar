/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:22:52 by jjaegle           #+#    #+#             */
/*   Updated: 2019/05/09 16:54:41 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*src_t;
	char	*dest_t;

	dest_t = (char*)dest;
	src_t = (char*)src;
	if (src < dest)
	{
		n = n - 1;
		while ((int)n >= 0)
		{
			dest_t[n] = src_t[n];
			n--;
		}
	}
	else
		ft_memcpy(dest, src, n);
	return (dest);
}
