/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:46:12 by thallot           #+#    #+#             */
/*   Updated: 2019/05/13 16:13:28 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
#include <inttypes.h>
#include <stdio.h>

static	int		ft_len(intmax_t value)
{
	int count;

	count = 1;
	while (value >= 10)
	{
		value /= 10;
		count++;
	}
	return (count);
}

char			*ft_itoa(intmax_t nb)
{
	static char		hex[] = "0123456789";
	char			*tab;
	intmax_t		abs;
	int				coef;
	int				sign;

	sign = nb < 0 ? 2 : 1;
	abs = ft_abs(nb);
	coef = ft_len(abs);
	if (!(tab = ft_strnew((coef + sign) - 1)))
		return (NULL);
	while (coef + sign - 2 >= 0)
	{
		tab[coef + sign - 2] = hex[abs % 10];
		abs /= 10;
		coef--;
	}
	if (sign == 2)
		tab[0] = '-';
	return (tab);
}
