/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 13:30:03 by thallot           #+#    #+#             */
/*   Updated: 2019/11/28 15:46:35 by thallot          ###   ########.fr       */
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
		mvwprintw(info, 31 + (i * 4), 6, "Last Live   %d     ",
				visu->vm->live[i]);
		mvwprintw(info, 32 + (i * 4), 6, "Nb Live     %d     ",
				visu->vm->nb_live[i]);
		wattron(info, COLOR_PAIR(i + 1));
		mvwprintw(info, 30 + (i * 4), 18, "%s",
				visu->vm->tab_champ.champs[i].name);
		wattroff(info, COLOR_PAIR(i + 1));
	}
}

void	print_menu(t_visu *visu, WINDOW *info)
{
	mvwprintw(info, 17, 3, "Cycle :          %d | %d    ",
			visu->rules->cycle, visu->rules->cr_cycle);
	wattron(info, A_UNDERLINE);
	mvwprintw(info, 10, 35, "RULES :");
	mvwprintw(info, 16, 35, "INFOS :");
	mvwprintw(info, 20, 35, "PARAMS :");
	mvwprintw(info, 24, 35, "LIVE BAR :");
	mvwprintw(info, 28, 35, "Player :");
	wattroff(info, A_UNDERLINE);
	mvwprintw(info, 11, 3, "CYCLE_TO_DIE %5d | %d  ",
			CYCLE_TO_DIE, visu->rules->cycle_to_die);
	mvwprintw(info, 12, 3, "CYCLE_DELTA  %5d |", CYCLE_DELTA);
	mvwprintw(info, 13, 3, "NBR_LIVE     %5d | %d  ",
			NBR_LIVE, visu->vm->cmpt_live);
	mvwprintw(info, 14, 3, "MAX_CHECKS   %5d | %d  ",
			MAX_CHECKS, visu->rules->nb_check);
	mvwprintw(info, 22, 3, "Speed : %d", 1000 - visu->speed);
}
