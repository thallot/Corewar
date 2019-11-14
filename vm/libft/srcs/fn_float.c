/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_float.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 09:01:34 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 16:48:32 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			only_zero(char *tabf)
{
	tabf++;
	while (*tabf)
	{
		if (*tabf != '0')
			return (0);
		tabf++;
	}
	return (1);
}

int			arround_int(char *tabint, char *tabf)
{
	int		i;

	i = 0;
	if (*tabf >= '5')
	{
		if (*tabf > '5' || tabint[ft_strlen(tabint) - 1] % 2 != 0)
		{
			ft_strrev(tabint);
			add_int(tabint, "1");
			ft_strrev(tabint);
			return (1);
		}
		else if (*tabf == '5' && tabint[ft_strlen(tabint) - 1] % 2 == 0)
		{
			if (!only_zero(tabf))
			{
				ft_strrev(tabint);
				add_int(tabint, "1");
				ft_strrev(tabint);
				return (1);
			}
		}
	}
	return (0);
}

int			apply_round(char *tab, int base, int pc)
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
		return (0);
	}
	return (0);
}

int			make_arrondi(t_float *fl, int prec)
{
	if (prec == 0)
		return (arround_int(fl->p_int, fl->p_dec));
	else if (apply_round(fl->p_dec, prec - 1, prec))
	{
		ft_strrev(fl->p_int);
		add_int(fl->p_int, "1");
		ft_strrev(fl->p_int);
		return (1);
	}
	return (0);
}

int			make_arrondiexp(t_exp *e, int prec)
{
	if (prec == 0)
		arrondi_expint(e);
	else if (apply_roundex(e->p_dec, prec - 1, prec))
	{
		if (e->p_int == '9')
		{
			e->p_int = '1';
			e->exp++;
		}
		else
			e->p_int++;
	}
	return (0);
}
