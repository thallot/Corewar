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

#include "../include/asm.h"

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
