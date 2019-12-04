/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:12:43 by thallot           #+#    #+#             */
/*   Updated: 2019/11/29 15:38:11 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	make_pause_exit(t_visu *visu, int opt)
{
	int c;

	if (opt == 0)
	{
		if (visu->pause == 0)
			timeout(visu->speed);
		else
			timeout(150000);
		if ((c = getch()) == 32)
			visu->pause = !visu->pause;
	}
}

void	get_speed(t_visu *visu)
{
	int c;

	while (visu->pause)
	{
		if ((c = getch()) == 32)
			visu->pause = !visu->pause;
		else if (c == 43)
		{
			visu->speed -= 10;
			visu->speed <= 0 ? visu->speed = 1 : visu->speed;
			visu_core(visu, 1);
		}
		else if (c == 45)
		{
			visu->speed += 10;
			visu->speed >= 400 ? visu->speed = 400 : visu->speed;
			visu_core(visu, 1);
		}
		else if (c == 27)
		{
			del_visu(visu);
			exit(clean_process(visu->process));
		}
	}
}

int		get_winner(t_visu *visu)
{
	int		i;
	t_listp	*tmp;

	tmp = visu->process;
	i = 0;
	while (tmp)
	{
		if (tmp->process.state != dead)
			i++;
		tmp = tmp->next;
	}
	if (i == 0)
	{
		visu->pause = 1;
		return (1);
	}
	if (visu->rules->cycle_to_die < CYCLE_DELTA
			&& visu->rules->cycle_to_die == 1)
	{
		visu->pause = 1;
		return (1);
	}
	visu->nb_process = i;
	return (0);
}
