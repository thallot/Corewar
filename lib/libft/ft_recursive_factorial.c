/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 15:37:46 by thallot           #+#    #+#             */
/*   Updated: 2019/02/10 09:57:20 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_recursive_factorial(int nb)
{
	int factoriel;
	int max;

	max = 2147483647;
	factoriel = 1;
	if (nb < 0)
		return (0);
	if (factoriel / max > nb)
		return (0);
	if (nb > 1)
		factoriel = nb * ft_recursive_factorial(nb - 1);
	return (factoriel);
}
