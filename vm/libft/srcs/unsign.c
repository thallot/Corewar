/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:49:59 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 10:16:10 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	fill_buffoct(unsigned long int h, t_print *print, t_bloc *bdi,
		t_buf *buf)
{
	int					zero;

	zero = (IS_ON(bdi->flags, ZERO)) ? 1 : 0;
	if (zero || IS_ON(bdi->flags, MOINS))
	{
		if (zero)
		{
			char_buf(buf, '0', print->padding);
			ultoa_base(buf, h, 10, print->prec);
			return ;
		}
		char_buf(buf, '0', print->prec);
		ultoa_base(buf, h, 10, print->prec);
		char_buf(buf, ' ', print->padding);
	}
	else
	{
		char_buf(buf, (zero) ? '0' : ' ', print->padding);
		char_buf(buf, '0', print->prec);
		ultoa_base(buf, h, 10, print->prec);
	}
}

static void	fill_printoct(t_print *p, unsigned long h, t_bloc *bdi)
{
	p->arg_len = ft_nbcarbase(h, 10);
	if (bdi->prec > -1)
	{
		if (bdi->prec == 0)
			p->prec = 0;
		else if (bdi->prec > p->arg_len + p->flags)
			p->prec = bdi->prec - p->arg_len - p->flags;
	}
	if (p->prec > -1)
		p->strlen = p->arg_len + p->prec + p->flags;
	else
		p->strlen = p->arg_len + p->flags;
	if (bdi->mfw > p->strlen)
		p->padding = bdi->mfw - p->strlen;
	if (!h && !bdi->prec && bdi->mfw > p->flags)
		p->padding++;
}

void		ft_is_uns(t_bloc *bdi, va_list ap, t_buf *buf)
{
	unsigned long int	u;
	t_print				print;

	if (COMP(bdi->modif, "l") || COMP(bdi->modif, "ll"))
		u = (unsigned long)va_arg(ap, long);
	else if (COMP(bdi->modif, "h"))
		u = (unsigned short)va_arg(ap, long);
	else if (COMP(bdi->modif, "hh"))
		u = (unsigned char)va_arg(ap, long);
	else
		u = (unsigned int)va_arg(ap, long);
	initialise_print(&print);
	fill_printoct(&print, u, bdi);
	fill_buffoct(u, &print, bdi, buf);
}
