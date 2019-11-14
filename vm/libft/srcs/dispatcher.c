/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 10:13:14 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/13 07:52:26 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/dispatcher.h"

void	dispatcher(t_bloc *bdi, va_list ap, t_buf *buf)
{
	int		i;

	i = 0;
	while (i < OPT)
	{
		if (bdi->type == g_dispatcher[i].c)
			g_dispatcher[i].f(bdi, ap, buf);
		i++;
	}
	initialise_bloc(bdi);
}
