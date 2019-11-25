/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 14:44:33 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/08 11:20:20 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int			color(const char **format, t_buf *buf)
{
	int size;

	if (!ft_strncmp(*format, "{red}", (size = 5)))
		fill_color(buf, PF_RED, size);
	else if (!ft_strncmp(*format, "{purple}", (size = 8)))
		fill_color(buf, PF_PURPLE, size);
	else if (!ft_strncmp(*format, "{yellow}", (size = 8)))
		fill_color(buf, PF_YELLOW, size);
	else if (!ft_strncmp(*format, "{blue}", (size = 6)))
		fill_color(buf, PF_BLUE, size);
	else if (!ft_strncmp(*format, "{green}", (size = 7)))
		fill_color(buf, PF_GREEN, size);
	else if (!ft_strncmp(*format, "{cyan}", (size = 6)))
		fill_color(buf, PF_CYAN, size);
	else if (!ft_strncmp(*format, "{white}", (size = 7)))
		fill_color(buf, PF_WHITE, size);
	else if (!ft_strncmp(*format, "{eoc}", (size = 5)))
		fill_color(buf, PF_EOC, size);
	*format = (*format) + size;
	return (0);
}

int			ft_printf(const char *format, ...)
{
	t_bloc	bdi;
	t_buf	buf;
	va_list	ap;

	initialise_bloc(&bdi);
	initialise_buf(&buf);
	va_start(ap, format);
	while (*format)
	{
		if (*format == '{')
			buf.cmpt += color(&format, &buf);
		if (*format != '%' && *format != '\0')
			char_buf(&buf, *format, 1);
		else if (*format != '\0')
		{
			buf.cmpt += ft_parsing(&format, &bdi, &buf, ap);
			if (bdi.type)
				dispatcher(&bdi, ap, &buf);
			continue ;
		}
		format++;
	}
	empty_buf(&buf);
	va_end(ap);
	return (buf.cmpt);
}
