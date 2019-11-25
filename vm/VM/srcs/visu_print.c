/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:36:17 by thallot           #+#    #+#             */
/*   Updated: 2019/11/25 11:21:59 by thallot          ###   ########.fr       */
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

	i = 0;
	if (visu->vm->lastlive != UNDEF)
	{
		wattron(info, COLOR_PAIR(visu->vm->lastlive + 1));
		mvwprintw(info, 29 + visu->vm->lastlive * 4, 3, "Player %s is alive",
		visu->vm->tab_champ.champs[visu->vm->lastlive].name);
		wattroff(info, COLOR_PAIR(visu->vm->lastlive + 1));
	}
	if (visu->rules->cycle_to_die == visu->rules->cr_cycle + 1)
		while (i < 4)
			mvwprintw(info, 29 + i++ * 4, 3, "%128c", ' ');
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
	mvwprintw(info, 18, 3, "Process number : %d", i);
}

void	print_info(t_visu *visu, WINDOW *info)
{
	print_player(visu, info);
	print_nb_process(visu, info);
	mvwprintw(info, 17, 3, "Cycle : %d", visu->rules->cycle);
	wattron(info, A_UNDERLINE);
	mvwprintw(info, 10, (COLS / 6) - 14, "RULES :");
	mvwprintw(info, 16, (COLS / 6) - 14, "INFOS :");
	mvwprintw(info, 20, (COLS / 6) - 14, "PARAMS :");
	mvwprintw(info, 27, (COLS / 6) - 14, "Player 1 :");
	mvwprintw(info, 31, (COLS / 6) - 14, "Player 2 :");
	mvwprintw(info, 35, (COLS / 6) - 14, "Player 3 :");
	mvwprintw(info, 39, (COLS / 6) - 14, "Player 4 :");
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
