/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:57:11 by thallot           #+#    #+#             */
/*   Updated: 2019/06/11 13:37:25 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			set_flag_float(t_arg *arg, int p, char *intp, char *decip)
{
	int len;
	int i;
	int y;

	y = 0;
	i = 0;
	len = ft_strlen(intp) + 1;
	if (arg->space && !arg->plus && arg->sign != 1)
		i = ft_put(' ', i);
	while (y + len + p + arg->plus + arg->space < arg->width && !arg->minus)
		y = arg->zero ? ft_put('0', y) : ft_put(' ', y);
	if (arg->plus || arg->sign == 1)
		i = arg->sign == 1 ? ft_put('-', i) : ft_put('+', i);
	ft_putstr(intp);
	if ((p || arg->sharp) && arg->sign != 2)
		i = ft_put('.', i);
	if (p != 0)
	{
		ft_putstr(decip);
		len += ft_strlen(decip);
	}
	while (y + len < arg->width - arg->plus - arg->space && arg->minus)
		y = arg->zero ? ft_put('0', y) : ft_put(' ', y);
	return (len + i + y - 1);
}

long double	ft_get_float(va_list list, t_arg *arg, char **intp, char **floatp)
{
	long double					nbr;
	int							i;
	int							k;

	k = 1;
	arg->precision = arg->flag_preci == 1 ? arg->precision : 6;
	if (arg->conv == MODIFIER_LF)
		nbr = va_arg(list, long double);
	else
		nbr = (double)va_arg(list, double);
	ftobinary(nbr, arg, 0);
	nbr = nbr < 0 ? -nbr : nbr;
	if (arg->precision == 0 && (nbr - (signed long int)nbr) >= 0.5)
		nbr += 0.5;
	*intp = ft_itoa((signed long int)nbr);
	nbr -= (signed long int)nbr;
	i = arg->precision;
	while (i--)
		k *= 10;
	nbr *= k;
	*floatp = ft_itoa((signed long int)(nbr + 0.5));
	while (ft_strlen(*floatp) < (size_t)arg->precision)
		*floatp = ft_joinc(*floatp, '0');
	return (nbr);
}

int			ft_print_float(va_list list, t_arg *arg)
{
	long double					nbr;
	char						*intp;
	char						*floatp;

	intp = NULL;
	floatp = NULL;
	nbr = ft_get_float(list, arg, &intp, &floatp);
	while (ft_strlen(floatp) < (size_t)arg->precision)
		floatp = ft_joinc(floatp, '0');
	if (arg->sign == 2)
	{
		arg->value = ft_strdup("nan");
		arg->len = 3;
		set_flag_str(arg, arg->len);
	}
	else
		arg->len = set_flag_float(arg, arg->precision, intp, floatp);
	ft_memdel((void**)&intp);
	ft_memdel((void**)&floatp);
	ft_memdel((void**)&(arg)->value);
	return (arg->len);
}
