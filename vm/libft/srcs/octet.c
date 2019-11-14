/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:49:59 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/07 16:49:55 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	fill_buffsharpoct(t_buf *buf)
{
	fill_buff(buf, "0");
}

static void	fill_buffoct(unsigned long int h, t_print *print, t_bloc *bdi,
		t_buf *buf)
{
	if (IS_ON(bdi->flags, ZERO) || IS_ON(bdi->flags, MOINS))
	{
		if (IS_ON(bdi->flags, SHARP))
			fill_buffsharpoct(buf);
		if (IS_ON(bdi->flags, ZERO))
		{
			char_buf(buf, '0', print->padding);
			if (print->flags == 0 || h != 0)
				ultoa_base(buf, h, 8, print->prec);
			return ;
		}
		char_buf(buf, '0', print->prec);
		if (print->flags == 0 || h != 0)
			ultoa_base(buf, h, 8, print->prec);
		char_buf(buf, ' ', print->padding);
	}
	else
	{
		char_buf(buf, ' ', print->padding);
		if (IS_ON(bdi->flags, SHARP))
			fill_buffsharpoct(buf);
		char_buf(buf, '0', print->prec);
		if (print->flags == 0 || h != 0)
			ultoa_base(buf, h, 8, print->prec);
	}
}

static void	fill_printoct(t_print *p, unsigned long h, t_bloc *bdi)
{
	if (IS_ON(bdi->flags, SHARP))
		p->flags = 1;
	p->arg_len = ft_nbcarbase(h, 8);
	if (bdi->prec > -1)
	{
		if (bdi->prec == 0)
			p->prec = 0;
		else if (bdi->prec > p->arg_len + p->flags)
			p->prec = bdi->prec - p->arg_len - p->flags;
		if (h == 0 && p->flags == 1 && p->prec)
			p->prec++;
	}
	if ((h == 0 && p->prec == 0) || (h == 0 && p->flags == 1))
		p->arg_len = 0;
	if (p->prec > -1)
		p->strlen = p->arg_len + p->prec + p->flags;
	else
		p->strlen = p->arg_len + p->flags;
	if (bdi->mfw > p->strlen)
		p->padding = bdi->mfw - p->strlen;
}

void		ft_is_oct(t_bloc *bdi, va_list ap, t_buf *buf)
{
	unsigned long int	o;
	t_print				print;

	if (COMP(bdi->modif, "l") || COMP(bdi->modif, "ll"))
		o = (unsigned long)va_arg(ap, long);
	else if (COMP(bdi->modif, "h"))
		o = (unsigned short)va_arg(ap, long);
	else if (COMP(bdi->modif, "hh"))
		o = (unsigned char)va_arg(ap, long);
	else
		o = (unsigned int)va_arg(ap, long);
	initialise_print(&print);
	fill_printoct(&print, o, bdi);
	fill_buffoct(o, &print, bdi, buf);
}
