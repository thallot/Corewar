/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:12:43 by thallot           #+#    #+#             */
/*   Updated: 2019/11/25 11:14:02 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void make_pause_exit(t_visu *visu, int opt)
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

void get_speed(t_visu *visu)
{
	int c;

	while (visu->pause)
	{
		if ((c = getch()) == 32)
			visu->pause = !visu->pause;
		else if (c == 43)
		{
			visu->speed -= 10;
			visu->speed <= 0 ? visu->speed = 10 : visu->speed;
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
			ft_memdel((void **)&(visu->memory));
			ft_memdel((void **)&(visu->info));
			endwin();
			exit(clean_process(visu->process));
		}
	}
}
