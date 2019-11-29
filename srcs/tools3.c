/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:19:53 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/29 12:02:43 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_size(int type, int d2)
{
	if (type == UNDEF)
		return (0);
	if (type == IND_CODE || (type == DIR_CODE && d2 == true))
		return (IND_SIZE);
	else if (type == DIR_CODE)
		return (DIR_SIZE);
	else
		return (T_REG);
}

/*
** remplace les valeurs initiales des parametres par leur valeur effective
** en se basant sur leur type
*/

void	set_param_value(unsigned char *mem, t_process *process, int i
		, int lg)
{
	unsigned char	*idx;

	if (process->param[i - 1].type == IND_CODE)
	{
		idx = &mem[get_adress(process->pc_instru
			, (short)process->param[i - 1].value, lg)];
		process->param[i - 1].value = change_endian(idx, REG_SIZE);
	}
	else if (process->param[i - 1].type == REG_CODE)
		process->param[i - 1].value =
			*(int*)process->records[process->param[i - 1].value - 1];
}

void	write_in_visu(int start, int dest, t_env *vm)
{
	int				nb_champ;
	int				cpt;

	nb_champ = vm->memory_visu[start] / 100;
	cpt = 4;
	while (cpt--)
		vm->memory_visu[(dest + cpt) % 4096] = nb_champ * 100 + BOLD_TURN;
}

void	del_visu(t_visu *visu)
{
	clear();
	while (1)
	{
		attron(COLOR_PAIR(1));
		if (visu->vm->lastlive != -1)
			mvprintw(LINES / 2 - 3, (COLS / 2) - 10
					, "Le joueur %d (%s) a gagné", visu->vm->lastlive
					, visu->vm->tab_champ.champs[visu->vm->lastlive].name);
		else
			mvprintw(LINES / 2 - 3, (COLS / 2) - 10
					, "No winner for today... Only looser");
		attroff(COLOR_PAIR(1));
		move(0, 0);
		timeout(150000);
		if (getch())
			break ;
	}
	endwin();
}
