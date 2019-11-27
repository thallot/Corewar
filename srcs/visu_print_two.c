/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:30:03 by thallot           #+#    #+#             */
/*   Updated: 2019/11/27 14:31:56 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	print_pause(t_visu *visu, WINDOW *info)
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

int		print_livebar_color(t_visu *visu, WINDOW *info, float live_percent[4])
{
	int i;
	int j;
	int total;

	i = -1;
	total = 12;
	while (++i < 4)
	{
		j = -1;
		if (live_percent[i])
		{
			while (++j < live_percent[i] / 2 && total + j < 62)
			{
				wattron(info, COLOR_PAIR(i + 1));
				mvwprintw(info, 26, total + j, "-");
				wattroff(info, COLOR_PAIR(i + 1));
			}
			total += j;
		}
	}
	return (total);
}

void	print_livebar(t_visu *visu, WINDOW *info, float live_percent[4])
{
	int j;
	int total;

	total = 12;
	j = -1;
	if (visu->vm->cmpt_live == 0)
	{
		while (++j < 50)
			mvwprintw(info, 26, 12 + j, "-");
		total = j + 12;
	}
	else
		total = print_livebar_color(visu, info, live_percent);
	mvwprintw(info, 26, 11, "[");
	mvwprintw(info, 26, 62, "]   ");
}

void	print_alive(t_visu *visu, WINDOW *info)
{
	int i;

	i = -1;
	while (++i < 4)
	{
		mvwprintw(info, 30 + (i * 4), 3, "Player [%d] ",
				visu->vm->tab_champ.champs[i].num);
		mvwprintw(info, 31 + (i * 4), 6, "Last Live   %d",
				visu->vm->live[i]);
		mvwprintw(info, 32 + (i * 4), 6, "Nb Live     %d",
				visu->vm->nb_live[i]);
		wattron(info, COLOR_PAIR(i + 1));
		mvwprintw(info, 30 + (i * 4), 18, "%s",
				visu->vm->tab_champ.champs[i].name);
		wattroff(info, COLOR_PAIR(i + 1));
	}
}
