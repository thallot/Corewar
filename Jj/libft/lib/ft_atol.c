/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <jjaegle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 17:41:36 by jjaegle           #+#    #+#             */
/*   Updated: 2019/10/28 09:43:19 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long		ft_atol(const char *str)
{
	long	rslt;
	long	neg;
	int		i;

	rslt = 0;
	neg = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\f' || str[i] == '\t'
			|| str[i] == '\r' || str[i] == '\v')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
		rslt = rslt * 10 + str[i++] - '0';
	return ((rslt * neg));
}
