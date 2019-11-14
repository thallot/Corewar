/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mask.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:11:40 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/10 09:38:12 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			get_signe(unsigned long l)
{
	return (l >> 63);
}

int			get_exposant(unsigned long l)
{
	l <<= 1;
	return ((l >> 53) - 1023);
}

int			get_exposant_long(unsigned long l)
{
	l <<= 49;
	return ((l >> 49) - 16383);
}

int			get_signe_long(unsigned long l)
{
	l <<= 48;
	return (l >> 63);
}

void		make_mask(unsigned long *l, t_mask *mask, int lg)
{
	if (lg > 0)
	{
		mask->signe = get_signe_long(l[1]);
		mask->e = get_exposant_long(l[1]);
		mask->l = *l;
	}
	else
	{
		mask->signe = get_signe(l[0]);
		mask->e = get_exposant(l[0]);
		*l <<= 12;
		*l >>= 12;
		mask->l = *l;
	}
}
