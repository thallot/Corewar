/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 08:08:28 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 14:59:56 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	flags_fl(t_buf *buf, unsigned char flags, int signe, char *s)
{
	if (!ft_strequ(s, "nan"))
	{
		if (signe == 0)
		{
			if (IS_ON(flags, PLUS))
				fill_buff(buf, "+");
			else if (IS_ON(flags, BLANK))
				fill_buff(buf, " ");
		}
		else
			fill_buff(buf, "-");
	}
}

static void	ft_putfloat(t_float *fl, int prec, unsigned char flags, t_buf *buf)
{
	if (fl->mask.e == 1024 || fl->mask.e == 16384)
	{
		fill_buff(buf, fl->p_int);
		return ;
	}
	if (prec == 0)
	{
		fill_buff(buf, fl->p_int);
		if (IS_ON(flags, SHARP))
			fill_buff(buf, ".");
		return ;
	}
	fill_buff(buf, fl->p_int);
	fill_buff(buf, ".");
	str_buf(buf, fl->p_dec, prec);
}

static void	print_float(t_float *fl, t_print *print, unsigned char flags,
		t_buf *buf)
{
	int					zero;

	zero = (IS_ON(flags, ZERO)) ? 1 : 0;
	if (make_arrondi(fl, print->prec))
		print->padding--;
	if (zero || IS_ON(flags, MOINS))
	{
		flags_fl(buf, flags, fl->mask.signe, fl->p_int);
		if (zero)
			char_buf(buf, '0', print->padding);
		ft_putfloat(fl, print->prec, flags, buf);
		if (IS_ON(flags, MOINS))
			char_buf(buf, ' ', print->padding);
	}
	else
	{
		char_buf(buf, ' ', print->padding);
		flags_fl(buf, flags, fl->mask.signe, fl->p_int);
		ft_putfloat(fl, print->prec, flags, buf);
	}
}

static void	fill_print(t_bloc *bdi, t_print *p, t_float *fl)
{
	p->prec = 0;
	p->flags = 0;
	OFF(bdi->flags, ZERO);
	if (ft_strequ(fl->p_int, "inf"))
		if ((IS_ON(bdi->flags, BLANK) || IS_ON(bdi->flags, PLUS))
				&& !fl->mask.signe)
			p->flags = 1;
	p->strlen = ft_strlen(fl->p_int) + p->flags;
	if (ft_strequ(fl->p_int, "inf"))
		if (fl->mask.signe)
			p->strlen += 1;
	p->padding = (bdi->mfw > p->strlen) ? bdi->mfw - p->strlen : 0;
}

void		ft_is_float(t_bloc *bdi, va_list ap, t_buf *buf)
{
	t_print			prt;
	t_float			fl;
	int				p;

	prt.flags = 0;
	make_fl(&fl, ap, (bdi->modif[0] == 'L') ? 1 : 0, bdi->prec);
	if (!fl.p_dec[0])
		fill_print(bdi, &prt, &fl);
	else
	{
		prt.prec = (bdi->prec > -1) ? bdi->prec : 6;
		p = (IS_ON(bdi->flags, SHARP) || prt.prec > 0) ? 1 : 0;
		prt.arg_len = ft_strlen(fl.p_int) + prt.prec + fl.mask.signe + p;
		if ((IS_ON(bdi->flags, BLANK) || IS_ON(bdi->flags, PLUS))
				&& !fl.mask.signe)
			prt.flags = 1;
		prt.strlen = prt.arg_len + prt.flags;
		prt.padding = (bdi->mfw > prt.strlen) ? bdi->mfw - prt.strlen : 0;
	}
	print_float(&fl, &prt, bdi->flags, buf);
}
