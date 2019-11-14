/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_exp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 14:00:46 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 15:17:50 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	add_one(t_exp *e)
{
	if (e->p_int == '9')
	{
		e->p_int = '1';
		e->exp++;
	}
	else
		e->p_int++;
}

void		arrondi_expint(t_exp *e)
{
	if (e->p_dec[0] >= '5')
	{
		if (e->p_dec[0] > '5')
			add_one(e);
		else if (e->p_dec[0] == '5' && e->p_int % 2 == 0)
		{
			if (!only_zero(e->p_dec))
				add_one(e);
		}
	}
}

int			apply_roundex(char *tab, int base, int pc)
{
	if (tab[pc] >= '5')
	{
		while (tab[base] == '9')
		{
			tab[base] = '0';
			if (base == 0)
				return (1);
			base--;
		}
		tab[base]++;
	}
	return (0);
}
