/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 11:09:00 by thallot           #+#    #+#             */
/*   Updated: 2019/04/19 17:31:39 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*str;
	size_t	i;
	size_t	size;

	str = NULL;
	if (s && f)
	{
		i = 0;
		size = ft_strlen(s);
		str = ft_strnew(size);
		if (str)
		{
			while (i < size)
			{
				str[i] = (*f)((unsigned int)i, s[i]);
				i++;
			}
		}
	}
	return (str);
}
