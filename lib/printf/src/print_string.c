/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 15:31:54 by thallot           #+#    #+#             */
/*   Updated: 2019/05/17 14:28:08 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		set_flag_str(t_arg *arg, int len)
{
	char *tmp;

	if (arg->flag_preci && arg->precision < len && arg->value[0] != '\0')
	{
		tmp = arg->value;
		arg->value = ft_strsub(arg->value, 0, arg->precision);
		ft_memdel((void **)&tmp);
		len = ft_strlen(arg->value);
	}
	if (arg->minus == 1)
	{
		ft_putstr(arg->value);
		while (len++ < arg->width)
			arg->zero == 1 ? ft_putchar('0') : ft_putchar(' ');
	}
	else
	{
		while (len++ < arg->width)
			arg->zero == 1 ? ft_putchar('0') : ft_putchar(' ');
		ft_putstr(arg->value);
	}
	return (len);
}

int		ft_print_string(va_list list, t_arg *arg)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
	if (arg->star)
		arg->width = va_arg(list, int);
	str = va_arg(list, char *);
	if (str == NULL)
		arg->value = ft_strdup("(null)");
	else
		arg->value = ft_strdup(str);
	len = ft_strlen(arg->value);
	len = set_flag_str(arg, len);
	ft_memdel((void **)&(arg)->value);
	return (len - 1);
}

int		ft_print_char(va_list list, t_arg *arg)
{
	int		c;
	int		i;
	int		n;

	n = 0;
	i = 0;
	c = va_arg(list, int);
	arg->nbr = c;
	if (arg->minus != 1)
	{
		while (n++ < arg->width - 1)
			i = arg->zero == 1 ? ft_put('0', i) : ft_put(' ', i);
		ft_putchar(c);
		i++;
	}
	else
	{
		ft_putchar(c);
		i++;
		while (n++ < arg->width - 1)
			i = arg->zero == 1 ? ft_put('0', i) : ft_put(' ', i);
	}
	arg->len = i;
	return (arg->len);
}

int		ft_print_percent(va_list list, t_arg *arg)
{
	int		c;
	int		i;
	int		n;

	n = 0;
	i = 0;
	c = '%';
	(void)list;
	arg->nbr = c;
	if (arg->minus != 1)
	{
		while (n++ < arg->width - 1)
			i = arg->zero == 1 ? ft_put('0', i) : ft_put(' ', i);
		ft_putchar(c);
		i++;
	}
	else
	{
		ft_putchar(c);
		i++;
		while (n++ < arg->width - 1)
			i = ft_put(' ', i);
	}
	arg->len = i;
	return (arg->len);
}
