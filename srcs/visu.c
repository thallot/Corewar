/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:36:27 by thallot           #+#    #+#             */
/*   Updated: 2019/11/25 16:02:02 by jjaegle          ###   ########.fr       */
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

void	print_corewar(t_visu *visu, WINDOW *info)
{
	wattron(info, COLOR_PAIR(1));
	mvwprintw(info, 1, 13, L_ONE);
	mvwprintw(info, 2, 13, L_TWO);
	mvwprintw(info, 3, 13, L_TRE);
	mvwprintw(info, 4, 13, L_FOU);
	mvwprintw(info, 5, 13, L_FIV);
	mvwprintw(info, 6, 13, L_SIX);
	wattroff(info, COLOR_PAIR(1));
}

int		is_process_position(t_visu *visu, int i)
{
	t_listp *tmp;

	tmp = visu->process;
	while (tmp)
	{
		if (tmp->process.pc == i && tmp->process.state != dead)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

void	init_visu(t_visu *visu, t_rules *rules, t_env *vm, t_listp *players)
{
	WINDOW *memory;
	WINDOW *info;

	initscr();
	keypad(stdscr, TRUE);
	noecho();
	start_color();
	use_default_colors();
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_BLUE, COLOR_BLACK);
	init_pair(3, COLOR_GREEN, COLOR_BLACK);
	init_pair(4, COLOR_YELLOW, COLOR_BLACK);
	print_intro();
	visu->rules = rules;
	visu->vm = vm;
	visu->vm->aff = 0;
	visu->process = players;
	visu->pause = 0;
	visu->speed = 100;
	memory = subwin(stdscr, LINES, 192, 0, 0);
	info = subwin(stdscr, LINES, 75, 0, 195);
	visu->memory = memory;
	visu->info = info;
	clear();
}

int		visu_core(t_visu *visu, int opt)
{
	WINDOW *memory;
	WINDOW *info;

	memory = visu->memory;
	info = visu->info;
	if (get_winner(visu) == 1)
		return (0);
	make_pause_exit(visu, opt);
	wmove(memory, 0, 0);
	wmove(info, 0, 0);
	curs_set(0);
	box(info, ACS_VLINE, ACS_HLINE);
	print_memory(visu, memory);
	print_info(visu, info);
	wrefresh(memory);
	wrefresh(info);
	get_speed(visu);
	return (0);
}
