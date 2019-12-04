/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:44:29 by thallot           #+#    #+#             */
/*   Updated: 2019/11/29 15:46:55 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ASM_H
# define FT_ASM_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "../lib/libft/libft.h"
# include "../lib/printf/includes/ft_printf.h"
# define TYPE_LIVE 1
# define TYPE_LD 2
# define TYPE_ST 3
# define TYPE_ADD 4
# define TYPE_SUB 5
# define TYPE_AND 6
# define TYPE_OR 7
# define TYPE_XOR 8
# define TYPE_ZJMP 9
# define TYPE_LDI 10
# define TYPE_STI 11
# define TYPE_FORK 12
# define TYPE_LLD 13
# define TYPE_LLDI 14
# define TYPE_LFORK 15
# define TYPE_AFF 16
# define TYPE_COMMAND 17
# define TYPE_STR 18
# define TYPE_LABEL 19
# define TYPE_LABEL_DEFINITION 20
# define TYPE_DIRECT_2 21
# define TYPE_DIRECT_4 22
# define TYPE_VIRGULE 23
# define TYPE_COMMENT 24
# define TYPE_INDEX 25
# define TYPE_REGISTRE 26
# define TYPE_DIRECT 27
# define TYPE_UNKNOWN 28
# define TYPE_NEWLINE 29

# define IND_SIZE 2
# define REG_SIZE	4
# define DIR_SIZE REG_SIZE
# define REG_CODE	1
# define DIR_CODE	2
# define IND_CODE	3
# define MAX_ARGS_NUMBER 4
# define MAX_PLAYERS 4
# define MEM_SIZE (4*1024)
# define IDX_MOD (MEM_SIZE / 8)
# define CHAMP_MAX_SIZE (MEM_SIZE / 6)
# define COMMENT_CHAR '#'
# define LABEL_CHAR ':'
# define DIRECT_CHAR '%'
# define SEPARATOR_CHAR ','
# define LABEL_CHARS "abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING ".name"
# define COMMENT_CMD_STRING ".comment"
# define REG_NUMBER 16
# define CYCLE_TO_DIE 1536
# define CYCLE_DELTA 50
# define NBR_LIVE 21
# define MAX_CHECKS 10
# define T_INSTRUCTION 1
# define T_OCP 1
# define T_REG 1
# define T_DIR 2
# define T_IND 4
# define T_LAB 8
# define PROG_NAME_LENGTH (128)
# define COMMENT_LENGTH (2048)
# define COREWAR_EXEC_MAGIC 0xea83f3

typedef char		t_arg_type;

typedef struct		s_gc
{
	void			*data;
	struct s_gc		*next;
}					t_gc;

typedef struct		s_lst
{
	int				type;
	char			*name;
	struct s_lst	*next;
}					t_lst;

typedef struct		s_env
{
	int				fd_s;
	int				fd_cor;
	char			*file_name;
	char			buffer[2];
	t_lst			*list;
	t_lst			*label;
	t_gc			*garbage_collector;
	void			(*parsing[21])(struct s_env *env);
	int				size;
}					t_env;

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

/*
*********************************** garbage_collector.c ************************
*/
void				del_garbage_collector(t_env *env);
int					exit_gc(t_env *env, int ret);
t_gc				*add_list_gc(t_env *env, void *data);
/*
*********************************** gc_functions.c *****************************
*/
void				*ft_memalloc_gc(size_t size, t_env *env);
char				*ft_strdup_gc(const char *s1, t_env *env);
char				*ft_strjoin_gc(char *s1, char const *s2, t_env *env);
char				*ft_strndup_gc(t_env *env, const char *s1, size_t n);
char				*ft_strndup_gc(t_env *env, const char *s1, size_t n);
/*
*********************************** Get_asm.c **********************************
*/
int					get_command(t_env *env);
int					get_str(t_env *env);
int					get_comment(t_env *env);
int					get_instruction(t_env *env);
int					get_char(int fd, char *buffer);
/*
*********************************** Main.c *************************************
*/
t_lst				*add_list(t_lst **list, char *name, int type, t_env *env);
char				*strjoinfree_gc(char *s1, char *s2, int opt, t_env *env);
int					is_blank(char c);
int					is_instruction(char *str);
int					is_separator(char c);
/*
*********************************** Tableau de fonctions ***********************
*/
int					loop_parser(t_env *env);
int					get_size(t_env *env);
void				exit_label_def(t_env *env, int opt, char c);
/*
*********************************** Tableau de fonctions ***********************
*/
void				is_valid_command(t_env *env);
void				is_valid_str(t_env *env);
void				is_valid_label(t_env *env);
void				is_valid_registre(t_env *env, char *instruction);
void				is_valid_add(t_env *env);
void				is_valid_sub(t_env *env);
void				is_valid_and(t_env *env);
void				is_valid_live(t_env *env);
void				is_valid_ld(t_env *env);
void				is_valid_st(t_env *env);
void				is_valid_or(t_env *env);
void				is_valid_xor(t_env *env);
void				is_valid_zjmp(t_env *env);
void				is_valid_ldi(t_env *env);
void				is_valid_sti(t_env *env);
void				is_valid_fork(t_env *env);
void				is_valid_lld(t_env *env);
void				is_valid_lldi(t_env *env);
void				is_valid_lfork(t_env *env);
void				is_valid_aff(t_env *env);
void				is_valid_label_call(t_env *env);
void				is_valid_label_definition(t_env *env);
int					is_valid_separator(t_env *env, char *ins, int one, int two);
void				print_error(t_env *env, char *instr, int nb);
/*
*********************************** Byte_ope.c *********************************
*/
int					generate_ocp(t_env *env);
void				ft_memrev(void *mask, size_t size);
void				zap_all(t_env *env, int opt);
int					looking_for_label(t_env *env, char *to_find);
/*
*********************************** file_parser.c ******************************
*/
int					parsing_file_s(t_env *env, char *file_path);
/*
*********************************** Writer.c ***********************************
*/
void				check_error(t_env *env, char *name);
void				w_header(t_env *env);
void				write_instr(t_env *env, int *cp_inst, int *cp_oct, int oct);
void				write_param(t_env *env, int *cpt_inst, int oct);
void				w_core(t_env *env);
/*
*********************************** Utils.c ************************************
*/
int					get_type_param(t_env *env);
void				add_elem(t_env *env, int type, char *inst, char last_char);
int					is_instruction_next(char *str);
int					is_instruction(char *str);
t_lst				*add_list(t_lst **list, char *name, int type, t_env *env);
/*
*********************************** util_parsing.c *****************************
*/
int					get_size(t_env *env);
void				print_error(t_env *env, char *instr, int nb);
int					is_valid_separator(t_env *env, char *ins, int one, int two);
int					is_valid_param(t_env *env, char *instruction);
void				is_valid_label_call(t_env *env);
void				print_lst(t_lst *list);
#endif
