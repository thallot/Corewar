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

void	print_player(t_visu *visu, WINDOW *info)
{
	int nb_player;
	int i;

	nb_player = visu->vm->tab_champ.nb_champ;
	i = 0;
	wattron(info, A_UNDERLINE);
	mvwprintw(info, 1, (COLS / 6) - 14, "PLAYERS (%d) :",
	visu->vm->tab_champ.nb_champ);
	wattroff(info, A_UNDERLINE);
	while (i < nb_player)
	{
		wattron(info, COLOR_PAIR(i + 1));
		mvwprintw(info, 3 + i, 3, "%s (Number : %d)",
		visu->vm->tab_champ.champs[i].name, visu->vm->tab_champ.champs[i].num);
		wattroff(info, COLOR_PAIR(i + 1));
		i++;
	}
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
