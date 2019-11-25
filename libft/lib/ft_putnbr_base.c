/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 11:55:42 by jjaegle           #+#    #+#             */
/*   Updated: 2019/05/23 08:22:10 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_base(unsigned long int nb, unsigned int b)
{
	static char			base[] = "0123456789ABCDEF";

	if (nb >= b)
		ft_putnbr_base(nb / b, b);
	ft_putchar(base[nb % b]);
}
