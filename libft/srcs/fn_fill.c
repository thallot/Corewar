/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_fill.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 14:13:14 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/11 17:28:47 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "../includes/ft_printf.h"
#define MAX_UL 65

static void	initialise_base(char *base, int maj)
{
	int		i;

	i = 0;
	while (i < 16)
	{
		if (i < 10)
			base[i] = '0' + i;
		else
			base[i] = (maj) ? 'A' + i - 10 : 'a' + i - 10;
		i++;
	}
}

void		ultoa_base(t_buf *buf, unsigned long ul, int b, int prec)
{
	char			base[16];
	char			res[MAX_UL];
	int				i;

	if (prec || ul)
	{
		initialise_base(base, 0);
		ft_bzero(res, MAX_UL);
		i = 0;
		if (ul == 0)
			res[i] = '0';
		while (ul > 0)
		{
			res[i++] = base[ul % b];
			ul /= b;
		}
		fill_buff(buf, ft_strrev(res));
	}
}

void		ultoa_maj(t_buf *buf, unsigned long ul, int b, int prec)
{
	char			base[16];
	char			res[MAX_UL];
	int				i;

	if (prec || ul)
	{
		initialise_base(base, 1);
		ft_bzero(res, MAX_UL);
		i = 0;
		if (ul == 0)
			res[i] = '0';
		while (ul > 0)
		{
			res[i++] = base[ul % b];
			ul /= b;
		}
		fill_buff(buf, ft_strrev(res));
	}
}

void		ltoa_base(t_buf *buf, long l, int b, int prec)
{
	char			base[16];
	char			res[MAX_UL];
	unsigned long	ul;
	int				i;

	if (prec || l)
	{
		initialise_base(base, 0);
		ft_bzero(res, MAX_UL);
		ul = (l < 0) ? -l : l;
		i = 0;
		if (ul == 0)
			res[i] = '0';
		while (ul > 0)
		{
			res[i++] = base[ul % b];
			ul /= b;
		}
		fill_buff(buf, ft_strrev(res));
	}
}

void		exptoa(t_buf *buf, int e)
{
	char			base[16];
	char			res[MAX_UL];
	int				i;

	i = 0;
	initialise_base(base, 0);
	if (e < 10)
		res[1] = '0';
	if (e == 0)
		res[i] = '0';
	while (e > 0)
	{
		res[i++] = base[e % 10];
		e /= 10;
	}
	fill_buff(buf, ft_strrev(res));
}
