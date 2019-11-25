/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 16:07:31 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/04 16:04:05 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void	print_char(unsigned char c, int padding, unsigned char flags
		, t_buf *buf)
{
	if (IS_ON(flags, MOINS))
	{
		char_buf(buf, c, 1);
		char_buf(buf, ' ', padding);
	}
	else
	{
		char_buf(buf, IS_ON(flags, ZERO) ? '0' : ' ', padding);
		char_buf(buf, c, 1);
	}
}

void		ft_is_char(t_bloc *bdi, va_list ap, t_buf *buf)
{
	unsigned char	c;
	int				padding;

	c = (unsigned char)va_arg(ap, int);
	padding = (bdi->mfw > 1) ? bdi->mfw - 1 : 0;
	print_char(c, padding, bdi->flags, buf);
}
