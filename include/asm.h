/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:44:29 by thallot           #+#    #+#             */
/*   Updated: 2019/11/04 15:44:30 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ASM_H
# define FT_ASM_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# define TYPE_COMMAND 1
# define TYPE_STR 2
# define TYPE_COMMENT 3
# define TYPE_INSTRUCTION 4
# define TYPE_VIRGULE 5
# define TYPE_LABEL_DEFINITION 6
# define TYPE_DIRECT 7
# define TYPE_INDEX 8
# define TYPE_REGISTRE 9
# define TYPE_LABEL 10
# define TYPE_UNKNOWN 11

# define IND_SIZE				2
# define REG_SIZE				4
# define DIR_SIZE				REG_SIZE
# define REG_CODE				1
# define DIR_CODE				2
# define IND_CODE				3
# define MAX_ARGS_NUMBER			4
# define MAX_PLAYERS				4
# define MEM_SIZE				(4*1024)
# define IDX_MOD					(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE			(MEM_SIZE / 6)
# define COMMENT_CHAR			'#'
# define LABEL_CHAR				':'
# define DIRECT_CHAR				'%'
# define SEPARATOR_CHAR			','
# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"
# define NAME_CMD_STRING			".name"
# define COMMENT_CMD_STRING		".comment"
# define REG_NUMBER				16
# define CYCLE_TO_DIE			1536
# define CYCLE_DELTA				50
# define NBR_LIVE				21
# define MAX_CHECKS				10
# define T_REG					1
# define T_DIR					2
# define T_IND					4
# define T_LAB					8
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
typedef char	t_arg_type;

typedef struct		header_s
{
  unsigned int		magic;
  char				prog_name[PROG_NAME_LENGTH + 1];
  unsigned int		prog_size;
  char				comment[COMMENT_LENGTH + 1];
}					header_t;

typedef struct				s_lst
{
	int 			type;
	char			*name;
	struct s_lst	*next;
}							t_lst;

/*
*********************************** Get_asm.c **********************************
*/
int get_command(int fd, char *buffer, t_lst *lst);
int get_str(int fd, char *buffer, t_lst *lst);
int get_comment(int fd, char *buffer, t_lst *lst);
int get_instruction(int fd, char *buffer, t_lst *lst);
int get_char(int fd, char *buffer);
/*
*********************************** Main.c *************************************
*/
t_lst	*add_list(t_lst **list, char *name, int type);
char	*strjoinfree(char *s1, char *s2, int opt);
int is_blank(char c);
int is_instruction(char *str);
int is_separator(char c);
#endif
