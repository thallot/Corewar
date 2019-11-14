/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strf.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:38:11 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 15:00:12 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		comp_len(int len, int strlen)
{
	if (len == strlen && len > 1)
		return (1);
	len = strlen;
	return (0);
}

void	multiply(char *tab, int nb)
{
	int		x;
	int		ret;
	int		cmpt;
	int		len;
	char	*tmp;

	tmp = tab;
	ret = 0;
	len = ft_strlen(tab);
	cmpt = 0;
	while (*tab)
	{
		if ((x = nb * (*tab - '0') + ret) < 10)
			*tab = x + '0';
		else
			*tab = x % 10 + '0';
		ret = x / 10;
		tab++;
	}
	if (ret)
		*tab++ = ret + '0';
	cmpt += comp_len(len, ft_strlen(tmp));
	while (nb == 5 && cmpt--)
		*tab++ = '0';
}

void	add_pow(char *tab, int e, int nb)
{
	char			temp[NB_CAR];

	ft_bzero(temp, NB_CAR);
	temp[0] = '1';
	while (e > 0)
	{
		multiply(temp, nb);
		e--;
	}
	if (nb == 2)
		add_int(tab, temp);
	else
		add_dec(tab, ft_strrev(temp));
}

void	make_add(t_float *f, short e)
{
	int				exp;

	exp = (e < 0) ? -(e) : e;
	if (e >= 0)
		add_pow(f->p_int, exp, 2);
	else
		add_pow(f->p_dec, exp, 5);
}

void	get_strfl(t_float *f, t_mask mask, int lg)
{
	unsigned long	z;
	int				z_shift;

	z_shift = (lg) ? 63 : 51;
	z = 1;
	z <<= z_shift;
	if (mask.e != -1023 && !lg)
	{
		make_add(f, mask.e);
		mask.e--;
	}
	while (z > 0)
	{
		if ((mask.l & z))
			make_add(f, mask.e);
		mask.e--;
		z >>= 1;
	}
	if (!f->p_int[0])
		f->p_int[0] = '0';
	ft_strrev(f->p_int);
}
