/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_mask.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 12:21:02 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 16:47:18 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_nan_inf(t_float *fl)
{
	if (fl->mask.e == 1024 || fl->mask.e == 16384)
	{
		if (fl->mask.l > 0)
			ft_strcpy(fl->p_int, "nan");
		else if (fl->mask.l == 0)
			ft_strcpy(fl->p_int, "inf");
		return (1);
	}
	return (0);
}

void	fill_dec(char *tab, int prec)
{
	int		i;
	int		end;

	end = (prec <= 0) ? 6 : prec;
	i = ft_strlen(tab);
	while (i < end)
		tab[i++] = '0';
}

int		calc_exp(t_float *fl, t_exp *e)
{
	int		i;

	if (!fl->p_int[1] && fl->p_int[0] == '0')
	{
		i = 0;
		while (fl->p_dec[i] == '0' && *fl->p_dec)
			i++;
		if (fl->p_dec[i])
		{
			e->p_int = fl->p_dec[i];
			return (i + 1);
		}
		e->p_int = '0';
		return (0);
	}
	e->p_int = *fl->p_int;
	return (ft_strlen(fl->p_int) - 1);
}

void	make_exp(t_float *fl, t_exp *e)
{
	if (ft_strequ(fl->p_int, "inf") || ft_strequ(fl->p_int, "nan"))
	{
		ft_strcpy(e->p_dec, fl->p_int);
		return ;
	}
	e->exp = calc_exp(fl, e);
	if (fl->p_int[1] || fl->p_int[0] != '0')
	{
		ft_strlcat(e->p_dec, fl->p_int + 1, NB_CAR);
		ft_strlcat(e->p_dec, fl->p_dec, NB_CAR);
		e->signe_exp = '+';
	}
	else
	{
		ft_strlcat(e->p_dec, fl->p_dec + e->exp, NB_CAR);
		e->signe_exp = '-';
	}
	if (e->p_int == '0')
		e->signe_exp = '+';
	e->signe = fl->mask.signe;
	e->len = (e->exp < 10) ? 4 : 2 + ft_nbcarlong(e->exp);
}

void	make_fl(t_float *fl, va_list ap, int lg, int prec)
{
	unsigned long	*ul;
	long double		ld;
	double			d;

	ft_bzero(fl->p_int, NB_CAR);
	ft_bzero(fl->p_dec, NB_CAR);
	if (lg == 1)
	{
		ld = va_arg(ap, long double);
		ul = (unsigned long*)&ld;
	}
	else
	{
		d = va_arg(ap, double);
		ul = (unsigned long*)&d;
	}
	make_mask(ul, &fl->mask, lg);
	if (is_nan_inf(fl))
		return ;
	get_strfl(fl, fl->mask, lg);
	fill_dec(fl->p_dec, prec);
}
