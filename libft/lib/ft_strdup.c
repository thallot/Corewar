/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 16:28:11 by jjaegle           #+#    #+#             */
/*   Updated: 2019/05/07 14:31:21 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strdup(const char *src)
{
	char	*str;
	size_t	len;

	str = NULL;
	if (src)
	{
		len = ft_strlen(src);
		if ((str = ft_strnew(len)) == NULL)
			return (NULL);
		str = (char*)ft_memcpy(str, src, len);
	}
	return (str);
}
