/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ptr.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:47:37 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 16:36:19 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		print_add(unsigned long int ul, t_print *print,
	t_bloc *bdi, t_buf *buf)
{
	if (IS_ON(bdi->flags, MOINS))
	{
		fill_buff(buf, "0x");
		char_buf(buf, '0', print->prec);
		ultoa_base(buf, ul, 16, bdi->prec);
		char_buf(buf, ' ', print->padding);
	}
	else if (IS_ON(bdi->flags, ZERO))
	{
		fill_buff(buf, "0x");
		char_buf(buf, '0', print->padding);
		ultoa_base(buf, ul, 16, bdi->prec);
	}
	else
	{
		char_buf(buf, ' ', print->padding);
		fill_buff(buf, "0x");
		char_buf(buf, '0', print->prec);
		ultoa_base(buf, ul, 16, bdi->prec);
	}
}

void			ft_is_add(t_bloc *bdi, va_list ap, t_buf *buf)
{
	unsigned long int	ul;
	t_print				pt;

	ul = (unsigned long)va_arg(ap, void*);
	pt.arg_len = ft_nbcarbase(ul, 16) + 2;
	pt.prec = (bdi->prec > pt.arg_len - 2) ? bdi->prec - pt.arg_len + 2 : 0;
	pt.strlen = pt.arg_len + pt.prec;
	pt.padding = (bdi->mfw > pt.strlen) ? bdi->mfw - pt.strlen : 0;
	print_add(ul, &pt, bdi, buf);
}
