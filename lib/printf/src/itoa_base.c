/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 13:54:56 by thallot           #+#    #+#             */
/*   Updated: 2019/05/29 11:34:46 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_itoa_base_uns(int base, t_arg *arg)
{
	unsigned int	value;
	int				i;
	int				count;
	char			*nbr;
	char			letters;

	value = arg->nbr;
	letters = arg->type == TYPE_XX ? 'A' : 'a';
	i = 1;
	while (ft_pow(base, i) - 1 < value)
		i++;
	count = i;
	nbr = (char*)ft_memalloc(sizeof(nbr) * i);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? letters - 10 : '0');
		value = value / base;
	}
	arg->len += count;
	arg->value = ft_strdup(nbr);
	ft_memdel((void**)&nbr);
	return (count);
}

int		ft_itoa_base_unsl(int base, t_arg *arg)
{
	unsigned long int	value;
	int					i;
	int					count;
	char				*nbr;
	char				letters;

	value = arg->nbr;
	letters = arg->type == TYPE_XX ? 'A' : 'a';
	count = 25;
	i = 25;
	nbr = (char*)ft_memalloc(sizeof(nbr) * 25);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? letters - 10 : '0');
		value = value / base;
	}
	i = 0;
	while (nbr[i] == '0')
		i++;
	arg->value = arg->nbr == 0 ? ft_strdup("0") : ft_strsub(nbr, i, 25 - i);
	arg->len = arg->nbr == 0 ? 1 : ft_strlen(arg->value);
	ft_memdel((void**)&nbr);
	return (arg->len);
}

int		ft_itoa_base_unsll(int base, t_arg *arg)
{
	uintmax_t			value;
	int					i;
	int					count;
	char				*nbr;
	char				letters;

	value = arg->nbr;
	letters = arg->type == TYPE_XX ? 'A' : 'a';
	count = 25;
	i = 25;
	nbr = (char*)ft_memalloc(sizeof(nbr) * 25);
	nbr[i] = '\0';
	while (i-- > 0)
	{
		nbr[i] = (value % base) + (value % base > 9 ? letters - 10 : '0');
		value = value / base;
	}
	i = 0;
	while (nbr[i] == '0')
		i++;
	arg->value = arg->nbr == 0 ? ft_strdup("0") : ft_strsub(nbr, i, 25 - i);
	arg->len = arg->nbr == 0 ? 1 : ft_strlen(arg->value);
	ft_memdel((void**)&nbr);
	return (arg->len);
}
