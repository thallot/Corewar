/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbrizon <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 11:02:39 by tbrizon           #+#    #+#             */
/*   Updated: 2019/06/26 11:02:41 by tbrizon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		print_prct(unsigned char c, int padding,
	unsigned char flags, t_buf *buf)
{
	char			zero;

	zero = IS_ON(flags, ZERO) ? 1 : 0;
	if (IS_ON(flags, MOINS))
	{
		char_buf(buf, c, 1);
		char_buf(buf, ' ', padding);
	}
	else
	{
		char_buf(buf, (zero) ? '0' : ' ', padding);
		char_buf(buf, c, 1);
	}
}

static int		ft_is_prct(t_bloc *bdi, unsigned char uc, t_buf *buf)
{
	unsigned char	c;
	int				padding;

	c = uc;
	padding = (bdi->mfw > 1) ? bdi->mfw - 1 : 0;
	print_prct(c, padding, bdi->flags, buf);
	return (0);
}

int				ft_is_bdi(const char **str)
{
	if (ft_is_in(str) == 1 || ft_is_in(str) == 2 || ft_isdigit(**str)
		|| **str == '.' || ft_is_in(str) == 3 || **str == '*')
		return (1);
	else
		return (0);
}

static void		ft_is_nt(t_bloc *bdi, t_buf *buf, const char **str)
{
	int		padding;
	int		zero;

	padding = (bdi->mfw > 1) ? bdi->mfw - 1 : 0;
	zero = IS_ON(bdi->flags, ZERO) ? 1 : 0;
	if (IS_ON(bdi->flags, MOINS))
	{
		char_buf(buf, **str, 1);
		char_buf(buf, ' ', padding);
	}
	else
	{
		char_buf(buf, IS_ON(bdi->flags, ZERO) ? '0' : ' ', padding);
		char_buf(buf, **str, 1);
	}
	(*str)++;
}

int				ft_parsing(const char **str, t_bloc *bloc,
	t_buf *buf, va_list ap)
{
	if (!*(*str + 1))
	{
		(*str)++;
		return (0);
	}
	*str = (*str) + 1;
	while (ft_is_bdi(str) && **str != '\0' && !jumpin(str, bloc, ap))
		;
	rules_flag(&bloc->flags, bloc->type, bloc->prec);
	if (!bloc->type && **str != '\0')
	{
		if (*(*str) == '%')
		{
			(*str)++;
			return (ft_is_prct(bloc, '%', buf));
		}
		else
		{
			ft_is_nt(bloc, buf, str);
			initialise_bloc(bloc);
		}
	}
	return (0);
}
