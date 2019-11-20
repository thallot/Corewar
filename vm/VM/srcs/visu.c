#include "op.h"
#include "vm.h"
#include <ncurses.h>

static void make_pause_exit(t_visu *visu, int opt)
{
  int c;

  if (opt == 0)
  {
    if (visu->pause == 0)
      timeout(visu->speed);
    else
      timeout(150000);
    if ((c = getch()) == 32)
      visu->pause = !visu->pause;
  }
}

static void get_speed(t_visu *visu)
{
  int c;

  while (visu->pause)
  {
    if ((c = getch()) == 32)
      visu->pause = !visu->pause;
    else if (c == 43)
    {
      visu->speed -= 10;
      visu->speed <= 00 ? visu->speed = 10 : visu->speed;
      visu_core(visu, 1);
    }
    else if (c == 45)
    {
      visu->speed += 10;
      visu_core(visu, 1);
    }
    else if (c == 27)
    {
      ft_memdel((void **)&(visu->memory));
      ft_memdel((void **)&(visu->info));
      endwin();
      exit(0);
    }
  }
}

static void print_player(t_visu *visu, WINDOW *info)
{
  int nb_player;
  int i;

  nb_player = visu->vm->tab_champ.nb_champ;
  i = 0;
  wattron(info, A_UNDERLINE);
  mvwprintw(info, 1, (COLS / 6) - 14, "PLAYERS (%d) :", visu->vm->tab_champ.nb_champ);
  wattroff(info, A_UNDERLINE);
  while (i < nb_player)
  {
    wattron(info, COLOR_PAIR(i + 1));
    mvwprintw(info, 3 + i, (COLS / 6) - 14, "%s (Number : %d)", visu->vm->tab_champ.champs[i].name, visu->vm->tab_champ.champs[i].num);
    wattroff(info, COLOR_PAIR(i + 1));
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
    if (tmp->process.state != dead)
      i++;
    tmp = tmp->next;
  }
  mvwprintw(info, 18, 3, "Process number : %d", i);
}

static int is_process_position(t_visu *visu, int i)
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

void print_info(t_visu *visu, WINDOW *info)
{
  print_player(visu, info);
  print_nb_process(visu, info);
  mvwprintw(info, 17, 3, "Cycle : %d", visu->rules->cycle);
  wattron(info, A_UNDERLINE);
  mvwprintw(info, 10, (COLS / 6) - 14, "RULES :");
  mvwprintw(info, 16, (COLS / 6) - 14, "INFOS :");
  mvwprintw(info, 20, (COLS / 6) - 14, "PARAMS :");
  wattroff(info, A_UNDERLINE);
  mvwprintw(info, 11, 3, "CYCLE_TO_DIE : %d", CYCLE_TO_DIE);
  mvwprintw(info, 12, 3, "CYCLE_DELTA : %d", CYCLE_DELTA);
  mvwprintw(info, 13, 3, "NBR_LIVE : %d", NBR_LIVE);
  mvwprintw(info, 14, 3, "MAX_CHECKS : %d", MAX_CHECKS);
  if (visu->pause)
    mvwprintw(info, 21, 3, "Pause : ON ");
  else
    mvwprintw(info, 21, 3, "Pause : OFF");
  mvwprintw(info, 22, 3, "Speed : %d", 1000 - visu->speed);
}

void init_visu(t_visu *visu, t_rules *rules, t_env *vm, t_listp *players)
{
  WINDOW *memory;
  WINDOW *info;

  initscr();
  while(1)
  {
      mvprintw(LINES/2, (COLS / 2) - 7, "Corewar");
      if (getch())
        break ;
  }
  visu->rules = rules;
  visu->vm = vm;
  visu->process = players;
  visu->pause = 0;
  visu->speed = 100;
  memory = subwin(stdscr, LINES, 192, 0, 0);
  info = subwin(stdscr, LINES, (COLS / 3) - 10 , 0, (COLS - COLS / 3) - 2);
  visu->memory = memory;
  visu->info = info;
  start_color();
  use_default_colors();
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_BLUE, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_YELLOW, COLOR_BLACK);
  clear();
}

void print_memory(t_visu *visu, WINDOW *memory)
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

int visu_core(t_visu *visu, int opt)
{
  WINDOW *memory;
  WINDOW *info;


  memory = visu->memory;
  info = visu->info;
  make_pause_exit(visu, opt);
  wmove(memory, 0 ,0);
  wmove(info, 0, 0);
  move(0, 0);
  box(info, ACS_VLINE, ACS_HLINE);
  print_memory(visu, memory);
  print_info(visu, info);
  wrefresh(memory);
  wrefresh(info);
  get_speed(visu);
  return (0);
}
