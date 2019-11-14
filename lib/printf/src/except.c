/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   except.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/11 13:53:39 by thallot           #+#    #+#             */
/*   Updated: 2019/06/18 12:34:38 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	exception_d(t_arg *arg, int *n)
{
	*n -= (arg->plus || arg->space || arg->nbr < 0) ? 1 : 0;
	*n -= (arg->plus && arg->zero && arg->nbr == 0) ? 1 : 0;
	*n -= (arg->len == arg->width && !arg->flag_preci) ? 1 : 0;
	*n -= (arg->len == 1 && arg->width > 1 && !arg->zero) ? 1 : 0;
	if (arg->width && arg->nbr && arg->conv && arg->zero && !arg->space)
		*n = *n - 1;
	*n += (arg->width > 1 && arg->flag_preci && arg->nbr == 0) ? 1 : 0;
	if (arg->type == TYPE_I)
	{
		if (arg->len == 1 && arg->flag_preci && arg->width == 1
				&& arg->width > 1 && !arg->plus)
			*n = *n - 1;
		if (arg->len == 1 && arg->flag_preci && arg->width > 1
				&& arg->width > 1 && !arg->plus && arg->zero)
			*n = *n - 1;
		if (arg->conv && arg->width && arg->flag_preci
				&& arg->nbr && !arg->space && arg->zero)
		{
			*n = *n + 1;
			if ((arg->conv == MODIFIER_HH || arg->conv == MODIFIER_H)
					&& arg->len == 1 && arg->zero && arg->plus)
				*n = *n - 1;
		}
	}
	arg->zero = (arg->zero && arg->flag_preci) ? 0 : arg->zero;
}

void	exception_u(t_arg *arg, int *n, int *p)
{
	if (arg->len == arg->width)
		*n = *n - 1;
	if (arg->len == 1 && arg->width == 1 && arg->flag_preci && !arg->precision)
		*n = *n + 1;
	if (arg->len == 1 && arg->width > 1 && !arg->flag_preci)
		*n = *n - 1;
	if (arg->len == 1 && arg->width > 1 && !arg->flag_preci && arg->zero)
		*n = *n + 1;
	if (arg->plus && arg->minus && arg->nbr && arg->len == 1)
		*n = *n + 1;
	if (arg->width > 1 && arg->zero && !arg->nbr && arg->width > 1 && arg->plus)
		*n = *n - 1;
	if (arg->width > 1 && arg->nbr && !arg->flag
			&& arg->len == 1 && !arg->precision)
		*n = *n + 1;
	(void)*p;
}

void	exception_o(t_arg *arg, int *n, int *p)
{
	if ((arg->sharp && arg->nbr) || (arg->sharp && arg->flag_preci))
		*n = *n - 1;
	if (!arg->flag && arg->width && !arg->flag_preci
			&& arg->len == 1 && arg->nbr)
		*n = *n + 1;
	if (arg->len == arg->width)
		*n = *n - 1;
	if (arg->len == 1 && arg->width == 1 && arg->flag_preci && !arg->precision)
		*n = *n + 1;
	if (arg->len == 1 && arg->width > 1 && !arg->flag_preci)
		*n = *n - 1;
	if (arg->len == 1 && arg->width > 1 && !arg->flag_preci && arg->zero)
		*n = *n + 1;
	if (arg->plus && arg->minus && arg->nbr && arg->len == 1)
		*n = *n + 1;
	if (arg->width > 1 && arg->zero && !arg->nbr && arg->width > 1 && arg->plus)
		*n = *n - 1;
	(void)*p;
}

void	exception_x(t_arg *arg, int *n, int *p)
{
	if (arg->sharp == 1 && arg->nbr != 0)
		*n = *n - 2;
	if (!arg->flag && arg->width && !arg->flag_preci
			&& arg->len == 1 && arg->nbr)
		*n = *n + 1;
	if (arg->len == arg->width)
		*n = *n - 1;
	if (arg->len == 1 && arg->width == 1 && arg->flag_preci && !arg->precision)
		*n = *n + 1;
	if (arg->len == 1 && arg->width > 1 && !arg->flag_preci)
		*n = *n - 1;
	if (arg->len == 1 && arg->width > 1 && !arg->flag_preci && arg->zero)
		*n = *n + 1;
	if (arg->plus && arg->minus && arg->nbr && arg->len == 1)
		*n = *n + 1;
	if (arg->width > 1 && arg->zero && !arg->nbr && arg->width > 1 && arg->plus)
		*n = *n - 1;
	if (arg->width && arg->conv && arg->sharp
			&& arg->len == 1 && !arg->precision && arg->nbr && !arg->zero)
		*n = *n + 1;
	(void)*p;
}

void	exception_f(t_arg *arg, int *n, int *p)
{
	if (arg->space && arg->nbr == 0)
		*n = *n + 1;
	if (arg->plus && arg->nbr == 0)
		*n = *n - 1;
	(void)*p;
}
