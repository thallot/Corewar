/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:46:59 by thallot           #+#    #+#             */
/*   Updated: 2019/04/08 09:47:02 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int i, int fd)
{
	unsigned int tmp;

	if (i < 0)
	{
		ft_putchar_fd('-', fd);
		tmp = -i;
	}
	else
		tmp = i;
	if (tmp >= 10)
		ft_putnbr_fd(tmp / 10, fd);
	ft_putchar_fd((tmp % 10) + 48, fd);
}
