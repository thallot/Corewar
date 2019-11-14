/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 07:42:09 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/13 07:52:29 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"
#include <limits.h>

void	ft_is_fd(t_bloc *bdi, va_list ap, t_buf *buf)
{
	int		fd;

	(void)bdi;
	fd = va_arg(ap, int);
	if (fd >= 0 && fd < OPEN_MAX)
		buf->fd = fd;
}
