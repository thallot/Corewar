/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:49:59 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 10:04:34 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	fill_buffsharpoct(t_buf *buf)
{
	fill_buff(buf, "b");
}

static void	fill_buffoct(unsigned long int h, t_print *print, t_bloc *bdi,
		t_buf *buf)
{
	int					zero;

	zero = (IS_ON(bdi->flags, ZERO)) ? 1 : 0;
	if (zero || IS_ON(bdi->flags, MOINS))
	{
		if (IS_ON(bdi->flags, SHARP) && h != 0)
			fill_buffsharpoct(buf);
		if (zero)
		{
			char_buf(buf, '0', print->padding);
			ultoa_base(buf, h, 2, print->prec);
			return ;
		}
		char_buf(buf, '0', print->prec);
		ultoa_base(buf, h, 2, print->prec);
		char_buf(buf, ' ', print->padding);
	}
	else
	{
		char_buf(buf, (zero) ? '0' : ' ', print->padding);
		if (IS_ON(bdi->flags, SHARP) && h != 0)
			fill_buffsharpoct(buf);
		char_buf(buf, '0', print->prec);
		ultoa_base(buf, h, 2, print->prec);
	}
}

static void	fill_printoct(t_print *p, unsigned long h, t_bloc *bdi)
{
	if (IS_ON(bdi->flags, SHARP) && h)
		p->flags = 1;
	p->arg_len = ft_nbcar_hd(h, bdi->prec);
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
}

void		ft_is_bin(t_bloc *bdi, va_list ap, t_buf *buf)
{
	unsigned long int	b;
	t_print				print;

	if (COMP(bdi->modif, "l") || COMP(bdi->modif, "ll"))
		b = (unsigned long)va_arg(ap, unsigned long);
	else if (COMP(bdi->modif, "h"))
		b = (unsigned short)va_arg(ap, unsigned int);
	else if (COMP(bdi->modif, "hh"))
		b = (unsigned char)va_arg(ap, unsigned int);
	else
		b = (unsigned int)va_arg(ap, unsigned int);
	initialise_print(&print);
	fill_printoct(&print, b, bdi);
	fill_buffoct(b, &print, bdi, buf);
}
