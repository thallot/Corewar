/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_initialise.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/06 13:16:44 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/05 16:44:38 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	fill_buff(t_buf *buf, char *str)
{
	while (buf->i < BUFF_SIZE && *str)
		buf->tab[buf->i++] = *str++;
	if (buf->i == BUFF_SIZE)
	{
		write(buf->fd, buf->tab, BUFF_SIZE);
		ft_bzero(buf->tab, BUFF_SIZE);
		buf->cmpt += buf->i;
		buf->i = 0;
		fill_buff(buf, str);
	}
}

void	empty_buf(t_buf *buf)
{
	write(buf->fd, buf->tab, buf->i);
	buf->cmpt += buf->i;
}

void	fill_color(t_buf *buf, char *color, int n)
{
	if (BUFF_SIZE - buf->i - 1 < n)
		empty_buf(buf);
	str_buf(buf, color, n);
}

void	str_buf(t_buf *buf, char *str, int n)
{
	char	*temp;

	temp = (str) ? str : "(null)";
	while (buf->i < BUFF_SIZE && n-- > 0 && *temp)
		buf->tab[buf->i++] = *temp++;
	if (buf->i == BUFF_SIZE)
	{
		write(buf->fd, buf->tab, BUFF_SIZE);
		ft_bzero(buf->tab, BUFF_SIZE);
		buf->cmpt += buf->i;
		buf->i = 0;
		str_buf(buf, temp, n);
	}
}

void	char_buf(t_buf *buf, char c, int nb)
{
	while (buf->i < BUFF_SIZE && nb-- > 0)
		buf->tab[buf->i++] = c;
	if (buf->i == BUFF_SIZE)
	{
		write(buf->fd, buf->tab, BUFF_SIZE);
		ft_bzero(buf->tab, BUFF_SIZE);
		buf->cmpt += buf->i;
		buf->i = 0;
		char_buf(buf, c, nb);
	}
}
