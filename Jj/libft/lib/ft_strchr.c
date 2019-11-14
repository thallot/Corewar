/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 19:17:50 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/18 09:35:06 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	if (s)
	{
		str = (char*)s;
		while (*str)
		{
			if (*str == (char)c)
				return (str);
			str++;
		}
		if (c == '\0')
			return (str);
	}
	return (NULL);
}
