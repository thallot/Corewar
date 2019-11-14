/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 10:04:22 by thallot           #+#    #+#             */
/*   Updated: 2019/05/17 13:48:02 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printf(const char *format, ...)
{
	va_list list;
	int		ret;

	ret = 0;
	va_start(list, format);
	ret = ft_print(format, list, 0, 0);
	va_end(list);
	return (ret);
}
