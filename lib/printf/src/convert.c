/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 15:07:35 by thallot           #+#    #+#             */
/*   Updated: 2019/05/17 10:44:14 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

intmax_t	conver_arg_s(t_arg *arg, va_list list)
{
	intmax_t nb;

	if (arg->conv == MODIFIER_L)
		nb = (long int)va_arg(list, long int);
	else if (arg->conv == MODIFIER_LL)
		nb = (long long int)va_arg(list, long long int);
	else if (arg->conv == MODIFIER_HH)
		nb = (char)va_arg(list, int);
	else if (arg->conv == MODIFIER_H)
		nb = (short int)va_arg(list, int);
	else if (arg->conv == MODIFIER_Z)
		nb = (size_t)va_arg(list, size_t);
	else if (arg->conv == MODIFIER_J)
		nb = (intmax_t)va_arg(list, intmax_t);
	else
		nb = va_arg(list, int);
	return (nb);
}

intmax_t	convert_arg_u(t_arg *arg, va_list list)
{
	intmax_t	nb;

	if (arg->conv == MODIFIER_L)
		nb = (unsigned long int)va_arg(list, uintmax_t);
	else if (arg->conv == MODIFIER_LL)
		nb = (uintmax_t)va_arg(list, uintmax_t);
	else if (arg->conv == MODIFIER_HH)
		nb = (unsigned char)va_arg(list, int);
	else if (arg->conv == MODIFIER_H)
		nb = (unsigned short int)va_arg(list, int);
	else if (arg->conv == MODIFIER_Z)
		nb = (ssize_t)va_arg(list, ssize_t);
	else if (arg->conv == MODIFIER_J)
		nb = (uintmax_t)va_arg(list, uintmax_t);
	else
		nb = va_arg(list, unsigned int);
	return (nb);
}

intmax_t	convert_arg(t_arg *arg, va_list list)
{
	intmax_t	nb;

	if (arg->type == TYPE_O || arg->type == TYPE_U || arg->type == TYPE_X
			|| arg->type == TYPE_XX)
		nb = convert_arg_u(arg, list);
	else
		nb = conver_arg_s(arg, list);
	return (nb);
}
