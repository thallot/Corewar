/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:53:59 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/13 15:04:39 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			nb_alive(t_listp *players)
{
	int		ret;

	ret = 0;
	while (players)
	{
		if (players->process.state != dead)
			ret++;
		players = players->next;
	}
	return (ret);
}

int		change_endian(void *var, int size)
{
	int		ret;

	ret = 0;
	ft_memcpy(&ret, var, size);
	ft_memrev(&ret, size);
	return (ret);
}

char		get_encoded(t_process *process, unsigned char memory[])
{
	process->pc++;
	return (memory[process->pc++]);
}

int			is_register(int tab[], int size)
{
	int		i;

	i = 0;
	while (i < size)
	{
		if (tab[i] < 1 || tab[i] > REG_NUMBER)
			return (0);
		i++;
	}
	return (1);
}
