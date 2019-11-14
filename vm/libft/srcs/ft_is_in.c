/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrizon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:42:53 by tbrizon           #+#    #+#             */
/*   Updated: 2019/06/13 07:53:12 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_is_modif(const char **str)
{
	if (**str == 'h' || **str == 'l' || **str == 'L' || **str == 'q'
		|| **str == 'j' || **str == 'z' || **str == 't')
		return (1);
	else
		return (0);
}

int		ft_is_type(const char **str)
{
	if (**str == 'd' || **str == 'i' || **str == 'u'
			|| **str == 'o' || **str == 'x' || **str == 'c' || **str == 'f'
		|| **str == 'e' || **str == 's' || **str == 'X' || **str == 'p'
		|| **str == 'b' || **str == 'w')
		return (1);
	else
		return (0);
}

int		ft_is_flag(const char **str)
{
	if (**str == '-' || **str == ' ' || **str == '+'
		|| **str == '#' || **str == '0')
		return (1);
	else
		return (0);
}

int		ft_is_in(const char **str)
{
	if (ft_is_type(str))
		return (1);
	if (ft_is_modif(str))
		return (2);
	if (ft_is_flag(str))
		return (3);
	return (0);
}
