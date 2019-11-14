/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:44:52 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/12 11:04:09 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_itoa(int n)
{
	int					i;
	int					j;
	char				*rslt;
	unsigned int		nb;
	int					neg;

	neg = 0;
	if (n < 0)
		neg = 1;
	nb = (neg) ? -n : n;
	i = 1;
	while ((n = n / 10))
		i++;
	if ((rslt = ft_strnew(i + neg)) == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		rslt[j++] = nb % 10 + '0';
		nb = nb / 10;
	}
	if (neg)
		rslt[i] = '-';
	return (ft_strrev(rslt));
}
