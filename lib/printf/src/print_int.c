/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 09:55:14 by thallot           #+#    #+#             */
/*   Updated: 2019/10/30 15:00:31 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_int(va_list list, t_arg *arg)
{
	if (arg->star)
		arg->width = va_arg(list, int);
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	arg->len = get_len_int(arg->nbr);
	set_flag_int(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}

int		ft_print_unsigned(va_list list, t_arg *arg)
{
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	arg->len = get_len_uint(arg->nbr);
	set_flag_uint(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}

int		ft_print_hex(va_list list, t_arg *arg)
{
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	if (!exep_hex(arg))
	{
		if (arg->conv == MODIFIER_LL || arg->conv == MODIFIER_J)
			ft_itoa_base_unsll(16, arg);
		else if (arg->conv == MODIFIER_L)
			ft_itoa_base_unsl(16, arg);
		else
			ft_itoa_base_uns(16, arg);
	}
	set_flag_hex(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}

int		ft_print_hexx(va_list list, t_arg *arg)
{
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	if (!exep_hexx(arg))
	{
		if (arg->conv == MODIFIER_LL || arg->conv == MODIFIER_J)
			ft_itoa_base_unsll(16, arg);
		else if (arg->conv == MODIFIER_L)
			ft_itoa_base_unsl(16, arg);
		else
			ft_itoa_base_uns(16, arg);
	}
	set_flag_hexx(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}

int		ft_print_oct(va_list list, t_arg *arg)
{
	arg->nbr = convert_arg(arg, list);
	arg = caster_int(arg);
	if (!exep_oct(arg))
	{
		if (arg->conv == MODIFIER_LL || arg->conv == MODIFIER_J)
			ft_itoa_base_unsll(8, arg);
		else if (arg->conv == MODIFIER_L)
			ft_itoa_base_unsl(8, arg);
		else
			ft_itoa_base_uns(8, arg);
	}
	set_flag_oct(arg, arg->len);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}
