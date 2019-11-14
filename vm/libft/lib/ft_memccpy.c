/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 15:58:57 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/12 10:15:26 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*dest_t;
	unsigned char	*src_t;
	size_t			i;

	dest_t = (unsigned char*)dest;
	src_t = (unsigned char*)src;
	i = 0;
	while (i < n)
	{
		dest_t[i] = src_t[i];
		if (src_t[i++] == (unsigned char)c)
			return (&dest_t[i]);
	}
	return (NULL);
}
