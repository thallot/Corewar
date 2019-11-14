/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 15:23:38 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/13 07:47:11 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		initialise_bloc(t_bloc *bdi)
{
	bdi->flags = 0;
	bdi->mfw = 0;
	bdi->prec = -1;
	bdi->type = 0;
	ft_memset(bdi->modif, '\0', 3);
}

void		initialise_buf(t_buf *buf)
{
	ft_bzero(buf->tab, BUFF_SIZE);
	buf->i = 0;
	buf->cmpt = 0;
	buf->fd = 1;
}

void		initialise_print(t_print *print)
{
	print->flags = 0;
	print->arg_len = 0;
	print->padding = 0;
	print->prec = -1;
	print->strlen = 0;
}
