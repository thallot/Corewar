/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_info.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 14:04:56 by thallot           #+#    #+#             */
/*   Updated: 2019/11/20 14:04:57 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "visu.h"
#include <ncurses.h>


void print_player(t_visu *visu, WINDOW *info)
{
  int nb_player;
  int i;

  nb_player = visu->vm->tab_champ.nb_champ;
  i = 0;
  mvwprintw(info, 1, (COLS / 6) - 14, "Players (%d) : ", visu->vm->tab_champ.nb_champ);
  while (i < nb_player)
  {
    mvwprintw(info, 3 + i, (COLS / 6) - 14, "%s (Number : %d)", visu->vm->tab_champ.champs[i].name, visu->vm->tab_champ.champs[i].num);
    i++;
  }
}

void print_nb_process(t_visu *visu, WINDOW *info)
{
  int i;
  t_listp *tmp;

  tmp = visu->process;
  i = 0;
  while (tmp)
  {
    tmp = tmp->next;
    i++;
  }
  mvwprintw(info, 15, 3, "Process number : %d", i);
}

int is_process_position(t_visu *visu, int i)
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
