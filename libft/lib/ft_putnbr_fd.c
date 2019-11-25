/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 17:32:22 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/07 12:46:35 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_putnbr_fd(int n, int fd)
{
	unsigned int	nb;

	if (n < 0)
		ft_putchar_fd('-', fd);
	nb = (n < 0) ? -n : n;
	if (nb / 10)
		ft_putnbr_fd((int)(nb / 10), fd);
	ft_putchar_fd(nb % 10 + '0', fd);
}
