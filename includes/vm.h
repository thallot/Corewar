/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:42:52 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/29 15:49:04 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/includes/ft_printf.h"
# include "op.h"
# include <ncurses.h>

# define NB_INSTR 16

# define UNINIT -2
# define UNDEF -1

# define READ 1
# define WRITE 2

# define DUMP 2
# define NUMBER 3
# define CHAMP 4
# define BIG 5
# define MAX 6
# define VISUAL 7

# define FIRST 1
# define SECND 2
# define THIRD 3

# define BOLD_TURN 90

/*
**--------------------------------Structures-----------------------
*/

enum				e_live{waiting, alive, dead};

/*
**t_result est un type representant un ptr sur fonction prenant 2 void*
*/

typedef void		(*t_result)(void*, void*);

/*
**s_param, recupere les parametres passe aux instructions
**ptr => adresse du parametre en memoire
**size => nombre d'octet du param
**value => valeur du parametre en little-endian
*/

typedef struct		s_param
{
	char			*ptr;
	int				value;
	int				type;
}					t_param;

/*
**un processeur peut etre vivant en attente ou mort(auquel cas il ne joue plus)
**et il peut etre actif, en cours d'execution d'une instruction pendant delay
**cycles, ou non.
**s'il est actif la callback sera executer apres delay cycles
*/

typedef struct		s_process
{
	int				active;
	char			records[REG_NUMBER][REG_SIZE];
	int				pc;
	int				pc_instru;
	int				carry;
	int				delay;
	enum e_live		state;
	t_param			param[MAX_ARGS_NUMBER];
	t_result		callback;
}					t_process;

/*
**lest des processeurs, seul entite malloc
*/

typedef struct		s_listp
{
	t_process		process;
	struct s_listp	*next;
}					t_listp;

/*
**un champ est represente par un numero, un nom et des instructions
*/

typedef struct		s_info_champ
{
	int				num;
	int				size;
	char			name[PROG_NAME_LENGTH + 1];
	char			instr[CHAMP_MAX_SIZE + 1];
}					t_info_champ;

/*
**Tableau de champion exploiter par la VM
*/

typedef struct		s_tabchamp
{
	int				nb_champ;
	t_info_champ	champs[MAX_PLAYERS];
}					t_tabchamp;

/*
**Variable permettant de faire tourner le corewar et d'avoir un vainqueur'
*/

typedef struct		s_rules
{
	int				cr_cycle;
	unsigned int	cycle;
	int				cycle_to_die;
	int				nb_verif;
	int				nb_check;
	int				someone_alive;
}					t_rules;

/*
**l'environnement de la vm
**lastlive => dernier champion ayant donne signe de vie
**nblive => nb de champion signale en vie depuis la derniere verif
*/

typedef struct		s_env
{
	unsigned char	memory[MEM_SIZE];
	unsigned int	memory_visu[MEM_SIZE];
	int				dump;
	t_tabchamp		tab_champ;
	t_listp			*player;
	int				lastlive;
	int				nblive;
	int				visu;
	int				cmpt_live;
	int				live[4];
	int				nb_live[4];
	t_rules			*rules;
	int				aff;
}					t_env;

typedef struct		s_visu
{
	t_listp			*process;
	t_env			*vm;
	t_rules			*rules;
	void			*memory;
	void			*info;
	int				pause;
	int				speed;
	int				nb_process;
}					t_visu;

/*
**--------------------------------Fn_champ----------------------------
*/

int					in_array(char *str, t_tabchamp *tab);
int					in_arraynb(int num, t_tabchamp *tab);
void				add_champ_num(int num, t_tabchamp *tab);
int					add_champ(char *file, t_tabchamp *tab);
void				adjust_num(t_tabchamp *tab);

/*
**--------------------------------Fn file---------------------------
*/

int					is_filechamp(char *file);
int					extract_info(char *file, t_info_champ *champ);

/*
**----------------------------------Fn game------------------------
*/

void				lets_play(t_env *vm);
int					create_process(t_env *vm);
void				process_play(t_listp *players, t_env *vm);

/*
**-------------------------------Instructions---------------------
*/

t_result			ft_ld(t_env *vm, t_process *process);
t_result			ft_live(t_env *vm, t_process *process);
t_result			ft_st(t_env *vm, t_process *process);
void				cb_st(void *pvm, void *pproc);
t_result			ft_add(t_env *vm, t_process *process);
t_result			ft_sub(t_env *vm, t_process *process);
t_result			ft_and(t_env *vm, t_process *process);
t_result			ft_or(t_env *vm, t_process *process);
t_result			ft_xor(t_env *vm, t_process *process);
t_result			ft_zjmp(t_env *vm, t_process *process);
t_result			ft_ldi(t_env *vm, t_process *process);
t_result			ft_sti(t_env *vm, t_process *process);
t_result			ft_fork(t_env *vm, t_process *process);
t_result			ft_lfork(t_env *vm, t_process *process);
t_result			ft_aff(t_env *vm, t_process *process);

/*
**----------------------------------Tools------------------------------
*/

int					print_error(int err, char *av[]);
void				dump_memory(unsigned char memory[]);
int					nb_alive(t_listp *players);
char				*get_param(t_process *process, unsigned char memory[]
		, int type, int d2);
int					get_params(t_process *process, unsigned char *memory
		, int nb, int d2);
int					get_size(int type, int d2);
char				get_encoded(t_process *process, unsigned char memory[]);
int					is_register(int tab[], int size);
int					val_record(t_process *process, int rec, int opt);
int					change_endian(void *var, int size);
int					get_adress(int start, int ind, int l);
int					clean_process(t_listp *list);
void				set_param_value(unsigned char *mem, t_process *process
		, int i, int lg);
void				del_visu(t_visu *visu);

/*
**----------------------------------Visu------------------------------
*/
void				init_visu(t_visu *visu, t_rules *rules, t_env *vm
		, t_listp *players);
int					visu_core(t_visu *visu, int opt);
void				write_in_visu(int start, int dest, t_env *vm);
void				print_intro();
void				print_live(WINDOW *info, t_visu *visu);
void				print_memory(t_visu *visu, WINDOW *memory);
void				init_visu(t_visu *visu, t_rules *rules, t_env *vm,
					t_listp *players);
int					is_process_position(t_visu *visu, int i);
void				print_info(t_visu *visu, WINDOW *info);
void				print_corewar(t_visu *visu, WINDOW *info);
void				print_nb_process(t_visu *visu, WINDOW *info);
void				get_speed(t_visu *visu);
void				make_pause_exit(t_visu *visu, int opt);
void				print_pause(t_visu *visu, WINDOW *info);
void				print_livebar(t_visu *visu, WINDOW *info
		, float live_percent[4]);
void				print_alive(t_visu *visu, WINDOW *info);
int					print_livebar_color(t_visu *visu, WINDOW *info
		, float live_percent[4]);
int					get_winner(t_visu *visu);
void				print_menu(t_visu *visu, WINDOW *info);
void				print_aff(t_visu *visu, WINDOW *info);

#endif
