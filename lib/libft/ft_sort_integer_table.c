/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_integer_table.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 19:03:04 by thallot           #+#    #+#             */
/*   Updated: 2019/04/09 15:49:38 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	ft_sort_integer_table(int *tab, size_t size)
{
	size_t	i;
	int		swap;

	i = 0;
	while (i < (size - 1))
	{
		if (tab[i + 1] < tab[i])
		{
			swap = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = swap;
			i = -1;
		}
		i++;
	}
}
