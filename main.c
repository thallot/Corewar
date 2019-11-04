/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:05:30 by thallot           #+#    #+#             */
/*   Updated: 2019/11/04 11:05:31 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include "libft/libft.h"
#define TYPE_COMMAND 1
#define TYPE_STR 2
#define TYPE_COMMENT 3
#define TYPE_INSTRUCTION 4
#define TYPE_VIRGULE 5
#define TYPE_LABEL 6
#define TYPE_DIRECT 7
#define TYPE_INDEX 8
#define TYPE_REGISTRE 9
#define TYPE_UNKNOWN 10

typedef struct				s_lst
{
	int 			type;
	char			*name;
	struct s_lst	*next;
}							t_lst;

t_lst	*add_list(t_lst **list, char *name, int type)
{
	t_lst *new;
	t_lst **head;

	head = list;
	if (!(new = (t_lst *)ft_memalloc((sizeof(t_lst)))))
		return (NULL);
	new->name = ft_strdup(name);
	new->type = type;
	new->next = NULL;
	if (!(*list))
		*list = new;
	else
	{
		while ((*list)->next)
			list = &(*list)->next;
		(*list)->next = new;
	}
	list = head;
	return (*head);
}

char	*strjoinfree(char *s1, char *s2, int opt)
{
	char *tmp;

	tmp = s1;
	s1 = ft_strjoin(s1, s2);
	if (opt >= 1)
		ft_strdel(&tmp);
	if (opt >= 2)
		ft_strdel(&s2);
	return (s1);
}

int get_char(int fd, char *buffer)
{
  int ret;

  ret = read(fd, buffer, 1);
  buffer[ret] = '\0';
  return (ret);
}

int is_blank(char c)
{
  if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f')
    return (1);
  return (0);
}

int is_instruction(char *str)
{
  if (!ft_strcmp("live", str) || !ft_strcmp("ld", str) || !ft_strcmp("st", str)
	|| !ft_strcmp("add", str) || !ft_strcmp("sub", str) || !ft_strcmp("and", str)
	|| !ft_strcmp("or", str) || !ft_strcmp("xor", str) || !ft_strcmp("zjmp", str)
	|| !ft_strcmp("ldi", str) || !ft_strcmp("sti", str) || !ft_strcmp("fork", str)
	|| !ft_strcmp("lld", str) || !ft_strcmp("lldi", str) || !ft_strcmp("lfork", str)
	|| !ft_strcmp("aff", str))
    return (1);
  return (0);
}

int is_separator(char c)
{
  if (c == ',')
    return (1);
  return (0);
}

int get_command(int fd, char *buffer, t_lst *lst)
{
  char *command;

  command = ft_strnew(0);
  while (!is_blank(buffer[0]))
  {
    command = strjoinfree(command, buffer, 1);
    get_char(fd, buffer);
  }
  add_list(&lst, command, TYPE_COMMAND);
  // printf("%s", command);
  return (1);
}

int get_str(int fd, char *buffer, t_lst *lst)
{
  char *comment;

  comment = ft_strnew(0);
	comment = strjoinfree(comment, buffer, 1);
	get_char(fd, buffer);
  while (buffer[0] != '"')
  {
    comment = strjoinfree(comment, buffer, 1);
    get_char(fd, buffer);
  }
	comment = strjoinfree(comment, buffer, 1);
	get_char(fd, buffer);
  add_list(&lst, comment, TYPE_STR);
  // printf("%s", comment);
  return (1);
}

int get_comment(int fd, char *buffer, t_lst *lst)
{
  char *comment;

  comment = ft_strnew(0);
	comment = strjoinfree(comment, buffer, 1);
	get_char(fd, buffer);
  while (buffer[0] != '\n')
  {
    comment = strjoinfree(comment, buffer, 1);
    get_char(fd, buffer);
  }
  add_list(&lst, comment, TYPE_COMMENT);
  // printf("%s", comment);
  return (1);
}

int get_instruction(int fd, char *buffer, t_lst *lst)
{
  char *instruction;
	int type;
	char last_char;

	if (buffer[0] == '%')
		type = TYPE_DIRECT;
	else if (ft_isdigit(buffer[0]))
		type = TYPE_INDEX;
	else if (buffer[0] == 'r')
		type = TYPE_REGISTRE;
	else
		type = TYPE_UNKNOWN;
  instruction = ft_strnew(0);
  while (!is_blank(buffer[0]) && !is_separator(buffer[0]))
  {
    instruction = strjoinfree(instruction, buffer, 1);
		last_char = buffer[0];
    get_char(fd, buffer);
  }
	if (last_char == ':')
		add_list(&lst, instruction, TYPE_LABEL);
	else
	{
		if (is_instruction(instruction))
			type = TYPE_INSTRUCTION;
		add_list(&lst, instruction, type);
	}
	if (buffer[0] == ',')
		add_list(&lst, buffer, TYPE_VIRGULE);
  // printf("%s", instruction);
	ft_strdel(&instruction);
  return (1);
}

void print_lst(t_lst *list)
{
	while (list)
	{
		printf("%-*s", 15, list->name);
		if (list->type == 0)
			printf("  -> (DEBUT)\n");
		if (list->type == TYPE_COMMAND)
			printf("  -> (COMMAND)\n");
		if (list->type == TYPE_STR)
			printf("  -> (STR POUR COMMAND)\n");
		if (list->type == TYPE_COMMENT)
			printf("  -> (COMMENT)\n");
		if (list->type == TYPE_INSTRUCTION)
			printf("  -> (INSTRUCTION)\n");
		if (list->type == TYPE_VIRGULE)
			printf("  -> (SEPARATEUR ' , ')\n");
		if (list->type == TYPE_LABEL)
			printf("  -> (DEFINITION LABEL)\n");
		if (list->type == TYPE_DIRECT)
			printf("  -> (PARAMETRE DIRECT)\n");
		if (list->type == TYPE_INDEX)
			printf("  -> (PARAMETRE INDEX)\n");
		if (list->type == TYPE_REGISTRE)
			printf("  -> (PARAMETRE REGISTRE)\n");
		if (list->type == TYPE_UNKNOWN)
			printf("  -> (ELEMENT INCONNU)\n");
		list = list->next;
	}
}

int main(int argc, char **argv)
{
  int fd;
  char buffer[2];
  t_lst *list;

  add_list(&list, "BEGIN", 0);
  if (argc > 1)
  {
    fd = open(argv[1], O_RDONLY );
    while (get_char(fd, buffer) > 0)
    {
      if (buffer[0] == '.')
        get_command(fd, buffer, list);
      if (buffer[0] == '"')
        get_str(fd, buffer, list);
			if (buffer[0] == '#')
				get_comment(fd, buffer, list);
			if (!is_blank(buffer[0]))
				get_instruction(fd, buffer, list);
      // printf("%s", buffer);
    }
		print_lst(list);
  }
  return (0);
}
