/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrizon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 19:40:02 by tbrizon           #+#    #+#             */
/*   Updated: 2019/06/07 16:53:46 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_parsing_flags(const char **str, unsigned char *flags)
{
	int		i;

	i = 0;
	while (**str == '-' || **str == ' ' || **str == '+'
		|| **str == '#' || **str == '0')
	{
		if (**str == '-')
			ON(*flags, MOINS);
		else if (**str == '+')
			ON(*flags, PLUS);
		else if (**str == ' ')
			ON(*flags, BLANK);
		else if (**str == '0')
			ON(*flags, ZERO);
		else if (**str == '#')
			ON(*flags, SHARP);
		(*str)++;
	}
}

void	ft_parsing_mfw(const char **str, int *mfw)
{
	int		i;

	i = 0;
	while (ft_isdigit(**str) && **str != 0)
	{
		i = i * 10;
		i = i + (**str - '0');
		(*str)++;
	}
	*mfw = i;
}

void	ft_parsing_precision(const char **str, int *prec, va_list ap)
{
	int		i;

	i = -1;
	if (**str == '.')
	{
		i = 0;
		(*str)++;
		if (**str == '*')
		{
			*prec = (int)va_arg(ap, long);
			((*str)++);
			return ;
		}
	}
	while (ft_isdigit(**str) && **str != 0)
	{
		i = i * 10;
		i = i + (**str - '0');
		(*str)++;
	}
	*prec = i;
}

void	ft_parsing_modif(const char **str, char *modif)
{
	int		i;

	i = 0;
	if (ft_is_in(str) == 2)
	{
		modif[0] = **str;
		(*str)++;
		if ((modif[i] == 'h' && **str == modif[i])
			|| (modif[i] == 'l' && **str == modif[i]))
		{
			modif[1] = **str;
			(*str)++;
		}
	}
}

void	ft_parsing_arg(const char **str, char *type)
{
	if (ft_is_in(str) == 1)
	{
		*type = **str;
		(*str)++;
	}
}
