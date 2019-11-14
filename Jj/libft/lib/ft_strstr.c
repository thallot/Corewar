/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:02:35 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/18 09:49:49 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strstr(const char *str, const char *word)
{
	const char	*find;
	const char	*tmp;

	if (!*word)
		return ((char*)str);
	while (str && *str)
	{
		find = str;
		tmp = word;
		while (*tmp && *tmp == *find)
		{
			find++;
			tmp++;
		}
		if (!*tmp)
			return ((char*)str);
		str++;
	}
	return (NULL);
}
