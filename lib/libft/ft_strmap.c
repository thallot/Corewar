/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:30:57 by thallot           #+#    #+#             */
/*   Updated: 2019/04/19 17:31:06 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
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
				str[i] = (*f)(s[i]);
				i++;
			}
		}
	}
	return (str);
}
