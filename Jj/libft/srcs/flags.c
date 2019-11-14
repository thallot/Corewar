/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:22:27 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/08 16:50:37 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_float(char type)
{
	if (type == 'f' || type == 'e')
		return (1);
	return (0);
}

void	rules_flag(unsigned char *flags, char type, int prec)
{
	if (IS_ON(*flags, ZERO) && type != 's')
		if (IS_ON(*flags, MOINS) || (!is_float(type) && prec >= 0))
			OFF(*flags, ZERO);
	if (IS_ON(*flags, PLUS) && IS_ON(*flags, BLANK))
		OFF(*flags, BLANK);
	if (IS_ON(*flags, PLUS) && IS_ON(*flags, SHARP))
	{
		if (is_base(type))
			OFF(*flags, PLUS);
		else if (type != 'f')
			OFF(*flags, SHARP);
	}
	else if (IS_ON(*flags, BLANK) && IS_ON(*flags, SHARP))
	{
		if (is_base(type))
			OFF(*flags, BLANK);
		else if (type != 'f')
			OFF(*flags, SHARP);
	}
}
