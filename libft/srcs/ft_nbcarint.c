/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbcarint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 08:17:20 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/11 13:48:38 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_nbcarlong(long int nb)
{
	unsigned long	u_nb;
	int				signe;
	int				car;

	u_nb = (nb < 0) ? -nb : nb;
	signe = (nb < 0) ? 1 : 0;
	car = 1;
	while ((u_nb /= 10))
		car++;
	return (car + signe);
}

int		ft_nbcarbase(unsigned long int nb, int base)
{
	int				car;

	car = 1;
	while ((nb /= base))
		car++;
	return (car);
}

int		ft_nbcar_hd(unsigned long int nb, int prec)
{
	if (prec || nb)
		return (ft_nbcarbase(nb, 16));
	return (0);
}
