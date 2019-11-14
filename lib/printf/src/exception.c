/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 14:56:08 by thallot           #+#    #+#             */
/*   Updated: 2019/06/11 13:11:55 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		exep_oct(t_arg *arg)
{
	if ((uintmax_t)arg->nbr == ULONG_MAX)
	{
		arg->value = ft_strdup("1777777777777777777777");
		arg->len = 22;
		return (arg->len);
	}
	return (0);
}

int		exep_hex(t_arg *arg)
{
	if ((uintmax_t)arg->nbr == ULLONG_MAX)
	{
		arg->value = ft_strdup("ffffffffffffffff");
		arg->len = 16;
		return (arg->len);
	}
	return (0);
}

int		exep_hexx(t_arg *arg)
{
	if ((uintmax_t)arg->nbr == ULLONG_MAX)
	{
		arg->value = ft_strdup("FFFFFFFFFFFFFFFF");
		arg->len = 16;
		return (arg->len);
	}
	return (0);
}

int		exep_int(t_arg *arg)
{
	if (arg->nbr == LONG_MIN)
	{
		arg->value = ft_strdup("9223372036854775808");
		arg->len = 17;
		return (arg->len);
	}
	return (0);
}

void	exception_o2(t_arg *arg, int *n, int *p)
{
	if (arg->width && arg->conv && arg->sharp
			&& arg->len == 1 && !arg->precision && arg->nbr && !arg->zero)
		*n = *n + 1;
	if (arg->sharp && arg->precision > arg->len && arg->nbr)
		*p = *p - 1;
	if (arg->sharp && arg->precision > arg->len && arg->width)
		*n = *n + 1;
	if (arg->sharp && arg->precision == 1 && arg->width && !arg->nbr)
		*n = *n + 1;
	if (arg->sharp && arg->width && arg->nbr && arg->len == 1
		&& !arg->flag_preci && !arg->conv)
		*n = *n + 1;
	if (arg->minus && !arg->sharp && arg->width && arg->nbr && arg->len == 1
		&& !arg->flag_preci && !arg->conv)
		*n = *n + 1;
	(void)*p;
}
