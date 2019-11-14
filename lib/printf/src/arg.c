/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/06 15:37:48 by thallot           #+#    #+#             */
/*   Updated: 2019/06/11 16:21:18 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	get_conv(const char *str, t_arg *arg, int *i)
{
	str[*i] == 'h' ? arg->conv = MODIFIER_H : arg->conv;
	str[*i] == 'l' ? arg->conv = MODIFIER_L : arg->conv;
	str[*i] == 'z' ? arg->conv = MODIFIER_Z : arg->conv;
	str[*i] == 'j' ? arg->conv = MODIFIER_J : arg->conv;
	str[*i] == 'L' ? arg->conv = MODIFIER_LF : arg->conv;
}

int		ft_print(const char *str, va_list list, int i, int count)
{
	int		len;
	t_arg	*arg;

	while (str[i])
	{
		if (str[i] == '%')
		{
			arg = get_arg(&str[i], &len);
			if (arg->type != -1)
			{
				count += ft_print_value(list, arg);
				str = str + len + i;
				i = 0;
			}
			else
				i = i + arg->len - 1;
			free_arg(arg);
		}
		else
		{
			i = ft_put(str[i], i);
			count++;
		}
	}
	return (count);
}

int		ft_print_value(va_list list, t_arg *arg)
{
	int				ret;
	int				(*f[13])(va_list, t_arg *);

	f[0] = &ft_print_binary;
	f[1] = &ft_print_float;
	f[2] = &ft_print_oct;
	f[3] = &ft_print_unsigned;
	f[4] = &ft_print_hexx;
	f[5] = &ft_print_hex;
	f[6] = &ft_print_pointer;
	f[7] = &ft_print_int;
	f[8] = &ft_print_char;
	f[9] = &ft_print_string;
	f[10] = &ft_print_percent;
	f[11] = &ft_print_i;
	f[12] = &ft_print_base;
	arg->len = 0;
	if (arg->type == -1)
		return (0);
	ret = f[arg->type](list, arg);
	return (ret);
}

int		ft_get_nb_arg(char *str)
{
	int		i;
	int		count;
	t_arg	*arg;
	int		len;

	len = 0;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i++] == '%')
		{
			if ((arg = get_arg(str, &len)) != NULL)
				count++;
		}
	}
	return (count);
}
