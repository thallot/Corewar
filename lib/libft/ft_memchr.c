/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 10:19:03 by thallot           #+#    #+#             */
/*   Updated: 2019/04/08 13:25:54 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*string;
	char	*ptr;

	string = (char *)s;
	ptr = NULL;
	i = 0;
	while (ptr == NULL && i < n)
	{
		if (string[i] == (char)c)
			ptr = string + i;
		i++;
	}
	return (ptr);
}
