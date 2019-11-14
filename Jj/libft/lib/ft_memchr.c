/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:46:56 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/12 10:17:16 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	*st;
	size_t	i;
	char	ct;

	ct = (char)c;
	st = (char*)s;
	i = 0;
	while (i < n)
		if (st[i++] == ct)
			return (&st[i - 1]);
	return (NULL);
}
