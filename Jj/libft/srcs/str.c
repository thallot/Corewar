/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:28:32 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 10:15:45 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		print_str(char *str, t_print *p, unsigned char flags,
		t_buf *buf)
{
	int		zero;

	zero = IS_ON(flags, ZERO) ? 1 : 0;
	if (IS_ON(flags, MOINS))
	{
		str_buf(buf, str, p->strlen);
		char_buf(buf, ' ', p->padding);
	}
	else
	{
		char_buf(buf, IS_ON(flags, ZERO) ? '0' : ' ', p->padding);
		str_buf(buf, str, p->strlen);
	}
}

void			ft_is_str(t_bloc *bdi, va_list ap, t_buf *buf)
{
	char	*str;
	t_print	print;

	str = (char*)va_arg(ap, void*);
	print.strlen = (str) ? ft_strlen(str) : 6;
	if (bdi->prec > -1)
		print.strlen = (bdi->prec < print.strlen) ? bdi->prec : print.strlen;
	print.padding = (bdi->mfw > print.strlen) ? bdi->mfw - print.strlen : 0;
	print_str(str, &print, bdi->flags, buf);
}
