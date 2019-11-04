/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 11:20:39 by thallot           #+#    #+#             */
/*   Updated: 2019/04/19 17:38:57 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	len_dst;
	size_t	len_src;
	int		i;

	i = 0;
	len_dst = 0;
	len_src = 0;
	while (dst[len_dst] != '\0')
		len_dst++;
	while (src[len_src] != '\0')
		len_src++;
	if (size < len_dst)
		return (size + len_src);
	while ((len_dst + i + 1) < size && src[i] != '\0')
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[i + len_dst] = '\0';
	return (len_dst + len_src);
}
