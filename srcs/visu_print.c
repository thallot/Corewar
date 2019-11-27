/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:36:17 by thallot           #+#    #+#             */
/*   Updated: 2019/11/25 15:49:44 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"
#define L_ONE " _____                                  "
#define L_TWO "/ ____|                                 "
#define L_TRE "| |     ___  _ __ _____      ____ _ _ __ "
#define L_FOU "| |    / _ \\| '__/ _ \\ \\ /\\ / / _` | '__|"
#define L_FIV "| |___| (_) | | |  __/\\ V  V / (_| | | "
#define L_SIX "\\_____\\___/|_|  \\___| \\_/\\_/ \\__,_|_| "
#define L_SEV ""

void	print_intro(void)
{
	while (1)
	{
		attron(COLOR_PAIR(1));
		mvprintw(LINES / 2 - 3, (COLS / 2) - 32, L_ONE);
		mvprintw(LINES / 2 - 2, (COLS / 2) - 32, L_TWO);
		mvprintw(LINES / 2 - 1, (COLS / 2) - 32, L_TRE);
		mvprintw(LINES / 2, (COLS / 2) - 32, L_FOU);
		mvprintw(LINES / 2 + 1, (COLS / 2) - 32, L_FIV);
		mvprintw(LINES / 2 + 2, (COLS / 2) - 32, L_SIX);
		mvprintw(LINES / 2 + 3, (COLS / 2) - 32, L_SEV);
		attroff(COLOR_PAIR(1));
		move(0, 0);
		if (getch())
			break ;
	}
}

void	print_live(WINDOW *info, t_visu *visu)
{
	int i;
	static int live[4];

	i = -1;
	while (++i < 4)
	{
		if (visu->vm->live[i] != 0)
		{
			wattron(info, COLOR_PAIR(i + 1));
			mvwprintw(info, 29 + i * 4, 3, "Player %s is alive (cycle : %d)",
			visu->vm->tab_champ.champs[i].name, visu->vm->live[i]);
			wattroff(info, COLOR_PAIR(i + 1));
		}
	}
	i = 0;
	if (visu->rules->cycle_to_die == visu->rules->cr_cycle + 1)
		while (i < 4)
			mvwprintw(info, 29 + i++ * 4, 3, "%128c", ' ');
	print_pause(visu, info);
}

void	print_memory(t_visu *visu, WINDOW *memory)
{
	int i;

	i = 0;
	wprintw(memory, "\n");
	while (i < MEM_SIZE)
	{
		if (visu->vm->memory_visu[i] != 0)
			wattron(memory, COLOR_PAIR(visu->vm->memory_visu[i]));
		if (is_process_position(visu, i))
		{
			wattron(memory, A_STANDOUT);
			wprintw(memory, " %02x", visu->vm->memory[i]);
			wattroff(memory, A_STANDOUT);
		}
		else
			wprintw(memory, " %02x", visu->vm->memory[i]);
		if (visu->vm->memory_visu[i] != 0)
			wattroff(memory, COLOR_PAIR(1));
		i++;
	}
}

void	print_nb_process(t_visu *visu, WINDOW *info)
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
	mvwprintw(info, 18, 3, "Process number : %-10d", i);
}

void	print_info(t_visu *visu, WINDOW *info)
{
	int i;

	i = 0;
	print_player(visu, info);
	print_nb_process(visu, info);
	mvwprintw(info, 17, 3, "Cycle : %d", visu->rules->cycle);
	wattron(info, A_UNDERLINE);
	mvwprintw(info, 10, 35, "RULES :");
	mvwprintw(info, 16, 35, "INFOS :");
	mvwprintw(info, 20, 35, "PARAMS :");
	while (i < visu->vm->tab_champ.nb_champ)
	{
		mvwprintw(info, 27 + i * 4, 35, "Player %d :",
		visu->vm->tab_champ.champs[i].num);
		i++;
	}
	wattroff(info, A_UNDERLINE);
	mvwprintw(info, 11, 3, "CYCLE_TO_DIE %5d | %d  ",
	CYCLE_TO_DIE, visu->rules->cycle_to_die);
	mvwprintw(info, 12, 3, "CYCLE_DELTA  %5d |", CYCLE_DELTA);
	mvwprintw(info, 13, 3, "NBR_LIVE     %5d | %d  ",
	NBR_LIVE, visu->vm->cmpt_live);
	mvwprintw(info, 14, 3, "MAX_CHECKS   %5d | %d  ",
	MAX_CHECKS, visu->rules->nb_check);
	print_live(info, visu);
	mvwprintw(info, 22, 3, "Speed : %d", 1000 - visu->speed);
}
