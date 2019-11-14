/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:11:42 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/12 10:45:14 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strnstr(const char *str, const char *word, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strcmp((char*)word, "") == 0)
		return ((char*)str);
	while (str[i] && i < len)
	{
		j = 0;
		while (str[i + j] == word[j] && i + j < len && str[i + j] && word[j])
			j++;
		if (!word[j])
			return ((char*)&str[i]);
		i++;
	}
	return (NULL);
}
