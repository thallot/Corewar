/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addition.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 16:09:18 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 10:55:28 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	add_int(char *src, const char *add)
{
	int		ret;
	int		x;

	ret = 0;
	if (!(*src))
	{
		ft_strcpy(src, add);
		return ;
	}
	while (*src && *add)
	{
		x = *src - '0' + *add - '0' + ret;
		*src++ = (x < 10) ? x + '0' : x % 10 + '0';
		ret = x / 10;
		add++;
	}
	while (*src)
	{
		x = *src - '0' + ret;
		*src++ = (x < 10) ? x + '0' : x % 10 + '0';
		ret = x / 10;
	}
	if (ret)
		*src = '1';
}

void	add_dec(char *src, const char *add)
{
	int		i;
	int		x;
	int		ret;

	i = ft_strlen(add);
	ret = 0;
	if (!(*src))
	{
		ft_strcpy(src, add);
		return ;
	}
	while (i >= 0)
	{
		if (src[i])
		{
			x = src[i] - '0' + add[i] - '0' + ret;
			src[i] = (x < 10) ? x + '0' : x % 10 + '0';
			ret = x / 10;
		}
		else
			src[i] = add[i];
		i--;
	}
}
