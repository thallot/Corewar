/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:42:52 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/14 15:34:46 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "../libft/includes/ft_printf.h"
# include "op.h"
# include <stdio.h>

# define NB_INSTR 11

# define UNINIT -2
# define UNDEF -1

# define READ 1
# define WRITE 2

# define DUMP 2
# define NUMBER 3
# define CHAMP 4
# define BIG 5
# define MAX 6

# define FIRST 1
# define SECND 2
# define THIRD 3

/*
**--------------------------------Structures-----------------------
*/

enum				e_bool{true, false};
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
	size_t			size;
	size_t			type;
}					t_param;

/*
**un processeur peut etre vivant en attente ou mort(auquel cas il ne joue plus)
**et il peut etre actif, en cours d'execution d'une instruction pendant delay
**cycles, ou non.
**s'il est actif la callback sera executer apres delay cycles
*/

typedef struct		s_process
{
	enum e_bool		active;
	char			records[REG_NUMBER][REG_SIZE];
	int				pc;
	enum e_bool		carry;
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
**l'environnement de la vm
**lastlive => dernier champion ayant donne signe de vie
**nblive => nb de champion signale en vie depuis la derniere verif
*/

typedef struct		s_env
{
	unsigned char	memory[MEM_SIZE];
	int				dump;
	t_tabchamp		tab_champ;
	t_listp			*player;
	int				lastlive;
	int				nblive;
}					t_env;

/*
**Variable permettant de faire tourner le corewar et d'avoir un vainqueur'
*/

typedef struct		s_rules
{
	unsigned int	cycle;
	int				cycle_to_die;
	int				nb_verif;
	int				nb_live;
	int				nb_check;
	enum e_bool		someone_alive;
}					t_rules;

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

void				lets_play(t_env *vm, t_listp *players);
int					create_process(t_env *vm);
void				process_play(t_listp *players, t_env *vm);

/*
**-------------------------------Instructions---------------------
*/

t_result				ft_ld(t_env *vm, t_process *process);
t_result			ft_live(t_env *vm, t_process *process);
t_result				ft_st(t_env *vm, t_process *process);
void					cb_st(void *pvm, void *pproc);
t_result				ft_add(t_env *vm, t_process *process);
t_result		ft_sub(t_env *vm, t_process *process);
t_result		ft_and(t_env *vm, t_process *process);
t_result		ft_or(t_env *vm, t_process *process);
t_result		ft_xor(t_env *vm, t_process *process);
t_result		ft_zjmp(t_env *vm, t_process *process);
t_result		ft_ldi(t_env *vm, t_process *process);
t_result		ft_sti(t_env *vm, t_process *process);

/*
**----------------------------------Tools------------------------------
*/

int					print_error(int err, char *av[]);
void				dump_memory(unsigned char memory[]);
int					nb_alive(t_listp *players);
char				*get_param(t_process *process, unsigned char memory[]
		, size_t size);
int					get_params(t_process *process, unsigned char *memory
		, int nb, enum e_bool d2);
int					get_size(char opcode, int param, enum e_bool d2);
char				get_encoded(t_process *process, unsigned char memory[]);
int					is_register(int tab[], int size);
int					val_record(t_process *process, int rec, int opt);
int					change_endian(void *var, int size);
int					get_adress(int start, int ind, enum e_bool l);

#endif
