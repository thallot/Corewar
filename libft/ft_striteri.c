/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:27:22 by thallot           #+#    #+#             */
/*   Updated: 2019/04/09 17:02:20 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	unsigned int i;
	unsigned int size;

	if (s && f)
	{
		i = 0;
		size = ft_strlen(s);
		while (i < size)
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}
