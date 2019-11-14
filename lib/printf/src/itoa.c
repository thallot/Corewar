/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 11:13:19 by thallot           #+#    #+#             */
/*   Updated: 2019/06/03 11:13:20 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static	int		ft_len(uintmax_t value)
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

char			*ft_uitoa(uintmax_t abs)
{
	static char		hex[] = "0123456789";
	char			*tab;
	int				coef;
	int				sign;

	sign = 1;
	coef = ft_len(abs);
	if (!(tab = ft_strnew((coef + sign) - 1)))
		return (NULL);
	while (coef + sign - 2 >= 0)
	{
		tab[coef + sign - 2] = hex[abs % 10];
		abs /= 10;
		coef--;
	}
	return (tab);
}
