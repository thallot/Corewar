/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 11:27:34 by thallot           #+#    #+#             */
/*   Updated: 2019/05/29 11:27:36 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		ft_put_all(char c, int *n, int *i)
{
	while ((*n)-- > 0)
	{
		ft_putchar(c);
		(*i)++;
	}
}

int			ft_put(char c, int i)
{
	ft_putchar(c);
	i++;
	return (i);
}

int			ft_putter(char *c, int i)
{
	ft_putstr(c);
	i += ft_strlen(c);
	return (i);
}

void		set_exception(t_arg *arg, int *n, int *p)
{
	if (arg->type == TYPE_D || arg->type == TYPE_I)
	{
		exception_d(arg, n);
		*n += (arg->width && arg->len == 1 && arg->nbr != 0) ? 1 : 0;
		*n -= (arg->all && arg->nbr && arg->len == 1) ? 1 : 0;
		*n -= (arg->zero && arg->len == 1 && arg->nbr) ? 1 : 0;
		*n += (arg->all && arg->nbr && arg->len == 1) ? 1 : 0;
		if (arg->conv && arg->width > arg->len && !arg->precision
				&& arg->nbr && !arg->space && arg->zero)
			*n = *n + 1;
		*n -= (arg->precision == 1 && arg->width == 1) ? 1 : 0;
	}
	if (arg->type == TYPE_U)
		exception_u(arg, n, p);
	if (arg->type == TYPE_O)
	{
		exception_o(arg, n, p);
		exception_o2(arg, n, p);
	}
	if (arg->type == TYPE_X || arg->type == TYPE_XX)
		exception_x(arg, n, p);
	if (arg->type == TYPE_F)
		exception_f(arg, n, p);
}

int			set_offset(int *len, t_arg *arg, intmax_t nb, int *p)
{
	int n;

	if (arg->type == TYPE_D || arg->type == TYPE_I)
		*len -= (nb < 0) ? 1 : 0;
	arg->plus = arg->type == TYPE_O ? 0 : arg->plus;
	*p = (arg->precision > *len) ? arg->precision - *len : 0;
	*len = (nb == 0 && arg->precision == 0) ? 0 : *len;
	n = arg->width - *len - *p;
	set_exception(arg, &n, p);
	n -= (arg->nbr == 0 && arg->zero && arg->width && !arg->plus) ? 1 : 0;
	n = n < 0 ? 0 : n;
	*p = *p < 0 ? 0 : *p;
	return (n);
}
