/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 11:44:07 by jjaegle           #+#    #+#             */
/*   Updated: 2019/05/07 11:33:19 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char		*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str;

	if (s && len)
	{
		if ((str = ft_strnew(len)) == NULL)
			return (NULL);
		ft_memcpy(str, s + start, len);
		return (str);
	}
	return (NULL);
}
