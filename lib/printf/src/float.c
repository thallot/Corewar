/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/17 09:29:31 by thallot           #+#    #+#             */
/*   Updated: 2019/06/17 10:31:45 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ftobinary(float f, t_arg *arg, int i)
{
	int				j;
	int				k;
	char			integer[9];
	char			deci[25];
	union u_decimal	fu;

	fu.f = f;
	i = sizeof(f) * CHAR_BIT;
	j = 0;
	k = 0;
	while (i--)
	{
		if (i == 31)
			arg->sign = (fu.u >> i) & 0x1;
		else if (i < 31 && i >= 23)
			integer[j++] = ((fu.u >> i) & 0x1) + '0';
		else
			deci[k++] = ((fu.u >> i) & 0x1) + '0';
	}
	i = 0;
	k = 0;
	while (integer[i] && integer[i++] == '1')
		k++;
	arg->sign = k == 8 ? 2 : arg->sign;
}

int		binary_int(char *str)
{
	int i;
	int expo;
	int nb;

	i = 0;
	expo = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '1')
			expo += ft_pow(2, 8 - i - 1);
		i++;
	}
	expo -= 127;
	expo > 0 ? nb = ft_pow(2, expo) : nb;
	return (nb);
}

void	binary_deci(char *str, int nbr)
{
	int		i;
	float	expo;
	int		nb;

	i = 0;
	expo = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] == '1')
			expo += (1 / ft_powf(2, i)) / 2;
		i++;
	}
	expo += 1;
	(void)nbr;
}
