/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:36:17 by thallot           #+#    #+#             */
/*   Updated: 2019/11/28 15:45:35 by jjaegle          ###   ########.fr       */
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
		attroff(COLOR_PAIR(1));
		move(0, 0);
		if (getch())
			break ;
	}
}

void	print_live(WINDOW *info, t_visu *visu)
{
	int		i;
	float	live_percent[4];

	print_alive(visu, info);
	i = -1;
	if (visu->rules->cycle_to_die == visu->rules->cr_cycle + 1)
		while (++i < 4)
			mvwprintw(info, 32 + i * 4, 3, "%128c", ' ');
	i = -1;
	while (++i < 4)
	{
		live_percent[i] = 0;
		if (visu->vm->nb_live[i] && visu->vm->cmpt_live)
			live_percent[i] = visu->vm->nb_live[i] * 100 / visu->vm->cmpt_live;
	}
	print_livebar(visu, info, live_percent);
}

void	print_memory(t_visu *visu, WINDOW *memory)
{
	int i;

	i = 0;
	wprintw(memory, "\n");
	while (i < MEM_SIZE)
	{
		if (visu->vm->memory_visu[i] != 0)
			wattron(memory, COLOR_PAIR(visu->vm->memory_visu[i] / 100));
		if (visu->vm->memory_visu[i] % 100 > 0)
			wattron(memory, A_BOLD);
		if (is_process_position(visu, i))
			wattron(memory, A_STANDOUT);
		wprintw(memory, " %02x", visu->vm->memory[i]);
		if (visu->vm->memory_visu[i] % 100 > 0)
		{
			wattroff(memory, A_BOLD);
			visu->vm->memory_visu[i]--;
		}
		if (visu->vm->memory_visu[i] != 0)
			wattroff(memory, COLOR_PAIR(visu->vm->memory_visu[i] / 100));
		if (is_process_position(visu, i))
			wattroff(memory, A_STANDOUT);
		i++;
	}
}

void	print_nb_process(t_visu *visu, WINDOW *info)
{
	mvwprintw(info, 18, 3, "Process number : %-10d", visu->nb_process);
}

void	print_info(t_visu *visu, WINDOW *info)
{
	int i;

	i = -1;
	print_corewar(visu, info);
	print_nb_process(visu, info);
	print_pause(visu, info);
	print_menu(visu, info);
	print_live(info, visu);
	print_aff(visu, info);
}
