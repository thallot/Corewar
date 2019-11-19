#include "op.h"
#include "vm.h"
#include <ncurses.h>

static void print_player(t_visu *visu, WINDOW *info)
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

static void print_nb_process(t_visu *visu, WINDOW *info)
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

static int is_process_position(t_visu *visu, int i)
{
  t_listp *tmp;

  tmp = visu->process;
  while (tmp)
  {
    if (tmp->process.pc == i)
      return (1);
    tmp = tmp->next;
  }
  return (0);
}

int visu_core(t_visu *visu)
{
  WINDOW *memory;
  WINDOW *info;
  int i;

  i = 0;
  clear();
  memory = subwin(stdscr, LINES, COLS / 2, 0, 0);
  info = subwin(stdscr, LINES, COLS / 3 , 0, COLS - COLS / 3);
  box(memory, ACS_VLINE, ACS_HLINE);
  box(info, ACS_VLINE, ACS_HLINE);
  wprintw(memory, "\n");
  while (i < MEM_SIZE)
  {
    if (i % 60 == 0)
      wprintw(memory, "\n");
    if (is_process_position(visu, i))
    {
      attron(A_UNDERLINE);
      wprintw(memory, " [%02x]", visu->vm->memory[i]);
      attroff(A_UNDERLINE);
    }
    else
      wprintw(memory, " %02x", visu->vm->memory[i]);
    i++;
  }
  print_player(visu, info);
  print_nb_process(visu, info);
  mvwprintw(info, 11, 3, "Cycle : %d", visu->rules->cycle);
  refresh();
  return (0);
}
