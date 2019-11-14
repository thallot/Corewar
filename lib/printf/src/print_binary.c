/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 16:24:48 by thallot           #+#    #+#             */
/*   Updated: 2019/05/30 16:24:49 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_binary(va_list list, t_arg *arg)
{
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	if (!exep_oct(arg))
	{
		if (arg->conv == MODIFIER_LL)
			ft_itoa_base_unsll(2, arg);
		else if (arg->conv == MODIFIER_L)
			ft_itoa_base_unsl(2, arg);
		else
			ft_itoa_base_uns(2, arg);
	}
	set_flag_oct(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}

int		ft_print_i(va_list list, t_arg *arg)
{
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	arg->len = get_len_int(arg->nbr);
	set_flag_int(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}

int		ft_print_base(va_list list, t_arg *arg)
{
	int base;

	base = arg->width;
	arg->width = 0;
	if (base < 1 || base > 17)
		base = 10;
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	if (!exep_hex(arg))
	{
		if (arg->conv == MODIFIER_LL || arg->conv == MODIFIER_J)
			ft_itoa_base_unsll(base, arg);
		else if (arg->conv == MODIFIER_L)
			ft_itoa_base_unsl(base, arg);
		else
			ft_itoa_base_uns(base, arg);
	}
	set_flag_hex(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}
