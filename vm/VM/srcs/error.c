/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 15:37:16 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/07 14:45:18 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			print_error(int err, char *av[])
{
	if (err == EXIT_FAILURE)
	{
		write(2, "Wrong parameter: ", 17);
		write(2, *av, ft_strlen(*av));
		write(2, "\n", 1);
		write(2, "Usage: ./corewar [-dump nbr_cycles] [[-n number]", 49);
		write(2, "champion1.cor] ...\n", 19);
	}
	else
	{
		if (err == DUMP)
			write(2, "dump error: ", 12);
		else if (err == NUMBER)
			write(2, "number error: ", 14);
		else if (err == CHAMP)
			write(2, "This file is not a champ: ", 26);
		else if (err == BIG)
			write(2, "Error: This champ is too fat: ", 30);
		else if (err == MAX)
			write(2, "4 champ needed, this one need to wait: ", 39);
		write(2, *av, ft_strlen(*av));
		write(2, "\n", 1);
	}
	return (EXIT_SUCCESS);
}
