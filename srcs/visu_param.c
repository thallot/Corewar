/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_param.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 11:12:43 by thallot           #+#    #+#             */
/*   Updated: 2019/11/25 11:25:42 by thallot          ###   ########.fr       */
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
			del_visu(visu);
			exit(clean_process(visu->process));
		}
	}
}

void print_pause(t_visu *visu, WINDOW *info)
{
	if (visu->pause)
	{
		wattron(info, COLOR_PAIR(3));
		mvwprintw(info, 21, 3, "Pause : ON ");
		wattroff(info, COLOR_PAIR(3));
	}
	else
	{
		wattron(info, COLOR_PAIR(1));
		mvwprintw(info, 21, 3, "Pause : OFF");
		wattroff(info, COLOR_PAIR(1));
	}
}
