/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:49:59 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 10:30:22 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	fill_buffsharphd(t_buf *buf, char type)
{
	if (type == 'x')
		fill_buff(buf, "0x");
	else
		fill_buff(buf, "0X");
}

static void	fill_result(unsigned long h, int prec, t_buf *buf, char type)
{
	if (type == 'x')
		ultoa_base(buf, h, 16, prec);
	else
		ultoa_maj(buf, h, 16, prec);
}

static void	fill_buffhd(unsigned long int h, t_print *print, t_bloc *bdi,
		t_buf *buf)
{
	int					zero;

	zero = (IS_ON(bdi->flags, ZERO)) ? 1 : 0;
	if (zero || IS_ON(bdi->flags, MOINS))
	{
		if (IS_ON(bdi->flags, SHARP) && h != 0)
			fill_buffsharphd(buf, bdi->type);
		if (zero)
		{
			char_buf(buf, '0', print->padding);
			fill_result(h, print->prec, buf, bdi->type);
			return ;
		}
		char_buf(buf, '0', print->prec);
		fill_result(h, print->prec, buf, bdi->type);
		char_buf(buf, ' ', print->padding);
	}
	else
	{
		char_buf(buf, (zero) ? '0' : ' ', print->padding);
		if (IS_ON(bdi->flags, SHARP) && h != 0)
			fill_buffsharphd(buf, bdi->type);
		char_buf(buf, '0', print->prec);
		fill_result(h, print->prec, buf, bdi->type);
	}
}

static void	fill_printhd(t_print *p, unsigned long h, t_bloc *bdi)
{
	if (IS_ON(bdi->flags, SHARP) && h)
		p->flags = 2;
	p->arg_len = ft_nbcar_hd(h, bdi->prec);
	if (bdi->prec > -1)
	{
		if (bdi->prec == 0)
			p->prec = 0;
		else
			p->prec = (bdi->prec > p->arg_len) ? bdi->prec - p->arg_len : -1;
	}
	if (p->prec > -1)
		p->strlen = p->arg_len + p->prec + p->flags;
	else
		p->strlen = p->arg_len + p->flags;
	if (bdi->mfw > p->strlen)
		p->padding = bdi->mfw - p->strlen;
}

void		ft_is_hexa(t_bloc *bdi, va_list ap, t_buf *buf)
{
	unsigned long int	h;
	t_print				print;

	if (COMP(bdi->modif, "l") || COMP(bdi->modif, "ll"))
		h = (unsigned long)va_arg(ap, long);
	else if (COMP(bdi->modif, "h"))
		h = (unsigned short)va_arg(ap, long);
	else if (COMP(bdi->modif, "hh"))
		h = (unsigned char)va_arg(ap, long);
	else
		h = (unsigned int)va_arg(ap, long);
	initialise_print(&print);
	fill_printhd(&print, h, bdi);
	fill_buffhd(h, &print, bdi, buf);
}
