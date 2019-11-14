/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 08:08:28 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 16:03:21 by jjaegle          ###   ########.fr       */
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

static void	ft_putexp(t_exp *e, int prec, t_buf *buf, unsigned char flags)
{
	char_buf(buf, e->p_int, 1);
	if (prec || IS_ON(flags, SHARP))
		char_buf(buf, '.', 1);
	str_buf(buf, e->p_dec, prec);
	char_buf(buf, 'e', 1);
	char_buf(buf, e->signe_exp, 1);
	exptoa(buf, e->exp);
	ft_bzero(e->p_dec, NB_CAR);
}

static void	print_float(t_exp *e, t_print *print, unsigned char flags,
		t_buf *buf)
{
	int					zero;

	zero = (IS_ON(flags, ZERO)) ? 1 : 0;
	make_arrondiexp(e, print->prec);
	if (zero || IS_ON(flags, MOINS))
	{
		flags_fl(buf, flags, e->signe, e->p_dec);
		if (zero)
			char_buf(buf, '0', print->padding);
		ft_putexp(e, print->prec, buf, flags);
		if (IS_ON(flags, MOINS))
			char_buf(buf, ' ', print->padding);
	}
	else
	{
		char_buf(buf, ' ', print->padding);
		flags_fl(buf, flags, e->signe, e->p_dec);
		ft_putexp(e, print->prec, buf, flags);
	}
}

static void	fill_print(t_bloc *bdi, t_print *p, t_exp *e)
{
	p->prec = 0;
	p->flags = 0;
	OFF(bdi->flags, ZERO);
	if (ft_strequ(e->p_dec, "inf"))
		if ((IS_ON(bdi->flags, BLANK) || IS_ON(bdi->flags, PLUS))
				&& !e->signe)
			p->flags = 1;
	p->strlen = ft_strlen(e->p_dec) + p->flags;
	if (ft_strequ(e->p_dec, "inf"))
		if (e->signe)
			p->strlen += 1;
	p->padding = (bdi->mfw > p->strlen) ? bdi->mfw - p->strlen : 0;
}

void		ft_is_exp(t_bloc *bdi, va_list ap, t_buf *buf)
{
	t_print			prt;
	t_float			fl;
	t_exp			exp;
	int				p;

	prt.flags = 0;
	make_fl(&fl, ap, (bdi->modif[0] == 'L') ? 1 : 0, bdi->prec);
	make_exp(&fl, &exp);
	if (!ft_isdigit(exp.p_dec[0]))
		fill_print(bdi, &prt, &exp);
	else
	{
		prt.prec = (bdi->prec > -1) ? bdi->prec : 6;
		p = (IS_ON(bdi->flags, SHARP) || prt.prec > 0) ? 1 : 0;
		prt.arg_len = 1 + prt.prec + exp.signe + p;
		if ((IS_ON(bdi->flags, BLANK) || IS_ON(bdi->flags, PLUS))
				&& !exp.signe)
			prt.flags = 1;
		prt.strlen = prt.arg_len + prt.flags + exp.len;
		prt.padding = (bdi->mfw > prt.strlen) ? bdi->mfw - prt.strlen : 0;
	}
	print_float(&exp, &prt, bdi->flags, buf);
}
