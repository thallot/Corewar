/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 09:37:16 by thallot           #+#    #+#             */
/*   Updated: 2019/06/11 13:13:54 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

uintmax_t		ft_uabs(intmax_t nb)
{
	return (nb > 0 ? nb : -nb);
}

int				get_len_int(intmax_t nb)
{
	int			len;
	intmax_t	n;

	len = 1;
	if (nb == LLONG_MIN)
		return (20);
	if (nb == LLONG_MAX)
		return (19);
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		len++;
		n = -nb;
	}
	else
		n = nb;
	while (n >= 10)
	{
		n /= 10;
		len++;
	}
	return (len);
}

int				get_len_uint(uintmax_t nb)
{
	int			len;

	len = 1;
	if (nb == ULLONG_MAX)
		return (20);
	if (nb == ULONG_MAX)
		return (10);
	if (nb == 0)
		return (1);
	while (nb >= 10)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

void			ft_putnbr_max(long long int nb)
{
	uintmax_t z;

	if (nb == LLONG_MIN)
	{
		ft_putstr("9223372036854775808");
		return ;
	}
	if (nb == LLONG_MAX)
	{
		ft_putstr("9223372036854775807");
		return ;
	}
	if (nb < 0)
		z = -nb;
	else
		z = nb;
	if (z >= 10)
		ft_putnbr(z / 10);
	ft_putchar((z % 10) + 48);
}

void			ft_putnbr_umax(uintmax_t nb)
{
	uintmax_t z;

	if (nb == ULLONG_MAX)
	{
		ft_putstr("18446744073709551615");
		return ;
	}
	if (nb == ULONG_MAX)
	{
		ft_putstr("4294967295");
		return ;
	}
	z = nb;
	if (z >= 10)
		ft_putnbr(z / 10);
	ft_putchar((z % 10) + 48);
}
