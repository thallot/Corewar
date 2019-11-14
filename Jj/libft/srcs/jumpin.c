/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jumpin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrizon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 10:15:44 by tbrizon           #+#    #+#             */
/*   Updated: 2019/06/26 10:15:46 by tbrizon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	jumpin(const char **str, t_bloc *bloc, va_list ap)
{
	if (**str == '*')
		star(str, bloc, ap);
	if (ft_is_in(str) == 3)
		ft_parsing_flags(str, &bloc->flags);
	if (ft_isdigit(**str))
		ft_parsing_mfw(str, &bloc->mfw);
	if (**str == '.')
		ft_parsing_precision(str, &bloc->prec, ap);
	if (ft_is_in(str) == 2)
		ft_parsing_modif(str, bloc->modif);
	if (ft_is_in(str) == 1)
	{
		ft_parsing_arg(str, &bloc->type);
		return (1);
	}
	return (0);
}
