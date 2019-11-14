/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   caster.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:51:58 by thallot           #+#    #+#             */
/*   Updated: 2019/05/17 10:40:41 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

t_arg	*caster_int(t_arg *arg)
{
	if (arg->type == TYPE_O || arg->type == TYPE_U || arg->type == TYPE_X
		|| arg->type == TYPE_XX)
		arg = caster_uint(arg);
	else
		arg = caster_sint(arg);
	return (arg);
}

t_arg	*caster_uint(t_arg *arg)
{
	if (arg->conv == MODIFIER_H)
		arg->nbr = (unsigned short)arg->nbr;
	else if (arg->conv == MODIFIER_HH)
		arg->nbr = (unsigned char)arg->nbr;
	else if (arg->conv == MODIFIER_L)
		arg->nbr = (unsigned long int)arg->nbr;
	else if (arg->conv == MODIFIER_LL)
		arg->nbr = (uintmax_t)arg->nbr;
	else if (arg->conv == MODIFIER_Z)
		arg->nbr = (size_t)arg->nbr;
	else if (arg->conv == MODIFIER_J)
		arg->nbr = (uintmax_t)arg->nbr;
	else
		arg->nbr = (unsigned int)arg->nbr;
	return (arg);
}

t_arg	*caster_sint(t_arg *arg)
{
	if (arg->conv == MODIFIER_LL)
		arg->nbr = (long long int)arg->nbr;
	else if (arg->conv == MODIFIER_L)
		arg->nbr = (long int)arg->nbr;
	else if (arg->conv == MODIFIER_H)
		arg->nbr = (short int)arg->nbr;
	else if (arg->conv == MODIFIER_HH)
		arg->nbr = (char)arg->nbr;
	else if (arg->conv == MODIFIER_Z)
		arg->nbr = (ssize_t)arg->nbr;
	else if (arg->conv == MODIFIER_J)
		arg->nbr = (intmax_t)arg->nbr;
	else
		arg->nbr = (int)arg->nbr;
	return (arg);
}
