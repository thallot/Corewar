/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 13:49:59 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/11 17:28:12 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	print_flags(t_buf *buf, long int l, unsigned char flags)
{
	if (l >= 0)
	{
		if (IS_ON(flags, PLUS))
			fill_buff(buf, "+");
		else if (IS_ON(flags, BLANK))
			fill_buff(buf, " ");
	}
	else
		fill_buff(buf, "-");
}

static void	fill_buffint(long int h, t_print *print, t_bloc *bdi,
		t_buf *buf)
{
	if (IS_ON(bdi->flags, ZERO) || IS_ON(bdi->flags, MOINS))
	{
		if (IS_ON(bdi->flags, ZERO))
		{
			print_flags(buf, h, bdi->flags);
			char_buf(buf, '0', print->padding);
			ltoa_base(buf, h, 10, print->prec);
			return ;
		}
		print_flags(buf, h, bdi->flags);
		char_buf(buf, '0', print->prec);
		ltoa_base(buf, h, 10, print->prec);
		char_buf(buf, ' ', print->padding);
	}
	else
	{
		char_buf(buf, ' ', print->padding);
		print_flags(buf, h, bdi->flags);
		char_buf(buf, '0', print->prec);
		ltoa_base(buf, h, 10, print->prec);
	}
}

static void	fill_printint(t_print *p, long h, t_bloc *bdi)
{
	p->arg_len = ft_nbcarlong(h);
	if (h >= 0 && (IS_ON(bdi->flags, PLUS) || IS_ON(bdi->flags, BLANK)))
		p->flags = 1;
	if (bdi->prec > -1)
	{
		if (bdi->prec == 0)
			p->prec = 0;
		else if (bdi->prec > (h >= 0) ? p->arg_len : p->arg_len - 1)
			p->prec = (h >= 0) ? bdi->prec - p->arg_len
				: bdi->prec - p->arg_len + 1;
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

void		ft_is_int(t_bloc *bdi, va_list ap, t_buf *buf)
{
	unsigned long int	d;
	t_print				print;

	if (COMP(bdi->modif, "l") || COMP(bdi->modif, "ll"))
		d = (long)va_arg(ap, long);
	else if (COMP(bdi->modif, "h"))
		d = (short)va_arg(ap, long);
	else if (COMP(bdi->modif, "hh"))
		d = (char)va_arg(ap, long);
	else
		d = (int)va_arg(ap, long);
	initialise_print(&print);
	fill_printint(&print, d, bdi);
	fill_buffint(d, &print, bdi, buf);
}
