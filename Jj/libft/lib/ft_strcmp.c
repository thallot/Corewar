/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 17:08:48 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/18 12:12:06 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int		i;

	i = 0;
	if (s1 && s2)
	{
		while (s1[i] && s1[i] == s2[i])
			i++;
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	}
	return (-1);
}
