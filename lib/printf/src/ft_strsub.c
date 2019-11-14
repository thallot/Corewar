/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:04:16 by thallot           #+#    #+#             */
/*   Updated: 2019/04/04 12:12:59 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char *str;

	str = NULL;
	if (s)
	{
		str = ft_strnew(len);
		if (!str)
			return (NULL);
		str = ft_strncpy(str, s + start, len);
	}
	return (str);
}
