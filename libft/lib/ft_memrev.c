/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/09 17:32:04 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/09 17:34:44 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memrev(void *mask, size_t size)
{
	size_t		i;
	size_t		j;
	char		tmp;
	char		*c;

	c = (char*)mask;
	i = 0;
	j = size - 1;
	while (i < j)
	{
		tmp = c[i];
		c[i] = c[j];
		c[j] = tmp;
		i++;
		j--;
	}
}
