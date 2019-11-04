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
# define TYPE_LABEL 6
# define TYPE_DIRECT 7
# define TYPE_INDEX 8
# define TYPE_REGISTRE 9
# define TYPE_UNKNOWN 10

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
