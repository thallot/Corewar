/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:55:04 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/12 11:03:06 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static int		first_char(char const *str)
{
	int		i;

	i = 0;
	while (ft_is_blank(str[i]) && str[i])
		i++;
	return (i);
}

static int		last_char(char const *str)
{
	int		i;

	i = ft_strlen((char*)str) - 1;
	while (ft_is_blank(str[i]) && i >= 0)
		i--;
	return (i);
}

char			*ft_strtrim(char const *s)
{
	int		start;
	int		end;
	char	*str;

	if (s)
	{
		start = first_char(s);
		end = last_char(s);
		if (end > start)
		{
			str = ft_strsub(s, start, end - start + 1);
			return (str);
		}
		str = (char*)malloc(sizeof(char));
		str[0] = '\0';
		return (str);
	}
	return (NULL);
}
