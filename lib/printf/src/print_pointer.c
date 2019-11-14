/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 14:25:42 by thallot           #+#    #+#             */
/*   Updated: 2019/05/29 12:02:15 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_pointer(va_list list, t_arg *arg)
{
	arg->nbr = va_arg(list, uintmax_t);
	arg->sharp = 1;
	arg->space = 0;
	arg->plus = 0;
	if (arg->nbr != 0 || arg->width > 0 || arg->precision)
	{
		ft_itoa_base_unsll(16, arg);
		arg->len = ft_strlen(arg->value);
		set_flag_point(arg, arg->len);
		ft_memdel((void **)&(arg)->value);
	}
	else if (arg->flag_preci == 1)
	{
		ft_putstr("0x");
		arg->len = 2;
	}
	else
	{
		ft_putstr("0x0");
		arg->len = 3;
	}
	ft_memdel((void **)&(arg)->value);
	return (arg->len);
}

void	set_flag_point(t_arg *arg, int len)
{
	int max;
	int p;
	int i;

	i = 0;
	max = set_offset(&len, arg, arg->nbr, &p);
	max = max - 2;
	if (arg->precision > arg->len)
		max++;
	if (arg->len == 1)
		max--;
	if (arg->zero && arg->nbr == 0)
		max++;
	if (!arg->minus && (arg->precision || !arg->zero))
		ft_put_all(' ', &max, &i);
	i = ft_putter("0x", i);
	if (arg->precision)
		ft_put_all('0', &p, &i);
	else if (!arg->minus && arg->zero)
		ft_put_all('0', &max, &i);
	if (!(arg->nbr == 0 && arg->flag_preci == 1 && arg->precision == 0))
		ft_putstr(arg->value);
	arg->nbr == 0 && arg->flag_preci == 1 && arg->precision == 0 ? i-- : i;
	ft_put_all(' ', &max, &i);
	arg->len = len == 0 ? i + 1 : i + len;
}
