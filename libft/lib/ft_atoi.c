/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/05 20:33:16 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/12 10:48:41 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	long	rslt;
	int		neg;
	int		i;

	rslt = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t' ||
				str[i] == '\n' || str[i] == '\r' ||
				str[i] == '\v')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		rslt = rslt * 10 + str[i++] - '0';
	return ((int)(rslt * neg));
}
