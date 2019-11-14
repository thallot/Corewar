/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:06:20 by thallot           #+#    #+#             */
/*   Updated: 2019/04/03 13:26:05 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	char	*ptr;
	size_t	len;

	i = 0;
	str = (char *)s;
	len = ft_strlen(str);
	ptr = NULL;
	while (i < len + 1)
	{
		if (str[i] == (char)c)
			ptr = (char *)s + i;
		i++;
	}
	return (ptr);
}
