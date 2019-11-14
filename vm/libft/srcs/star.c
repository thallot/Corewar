/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrizon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/18 13:35:25 by tbrizon           #+#    #+#             */
/*   Updated: 2019/06/18 13:35:26 by tbrizon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	star(const char **str, t_bloc *bdi, va_list ap)
{
	bdi->mfw = (int)va_arg(ap, long);
	if (bdi->mfw < 0)
	{
		ON(bdi->flags, MOINS);
		bdi->mfw *= -1;
	}
	(*str)++;
}
