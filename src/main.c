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

t_lst	*add_list(t_lst **list, char *name, int type, t_env *env)
{
	t_lst *new;
	t_lst **head;

	head = list;
	new = (t_lst *)ft_memalloc_gc((sizeof(t_lst)), env);
	new->name = name;
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

int is_blank(char c)
{
  if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f')
    return (1);
  return (0);
}

int is_instruction(char *str)
{
  if (!ft_strcmp("live", str))
		return (TYPE_INSTRUCTION_LIVE);
	else if (!ft_strcmp("ld", str))
		return (TYPE_INSTRUCTION_LD);
 	else if (!ft_strcmp("st", str))
		return (TYPE_INSTRUCTION_ST);
	else if (!ft_strcmp("add", str))
		return (TYPE_INSTRUCTION_ADD);
	else if (!ft_strcmp("sub", str))
		return (TYPE_INSTRUCTION_SUB);
	else if (!ft_strcmp("and", str))
		return (TYPE_INSTRUCTION_AND);
	else if (!ft_strcmp("or", str))
		return (TYPE_INSTRUCTION_OR);
	else if (!ft_strcmp("xor", str))
		return (TYPE_INSTRUCTION_XOR);
	else if (!ft_strcmp("zjmp", str))
		return (TYPE_INSTRUCTION_ZJMP);
	else if (!ft_strcmp("ldi", str))
		return (TYPE_INSTRUCTION_LDI);
	else if (!ft_strcmp("sti", str))
		return (TYPE_INSTRUCTION_STI);
	else if (!ft_strcmp("fork", str))
		return (TYPE_INSTRUCTION_FORK);
	else if (!ft_strcmp("lld", str))
		return (TYPE_INSTRUCTION_LLD);
	else if (!ft_strcmp("lldi", str))
		return (TYPE_INSTRUCTION_LLDI);
	else if (!ft_strcmp("lfork", str))
		return (TYPE_INSTRUCTION_LFORK);
	else if (!ft_strcmp("aff", str))
		return (TYPE_INSTRUCTION_AFF);
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
		printf("%-15s", list->name);
		if (list->type == 0)
			printf("  -> (DEBUT)\n");
		if (list->type == TYPE_COMMAND)
			printf("  -> (COMMAND)\n");
		if (list->type == TYPE_STR)
			printf("  -> (STR POUR COMMAND)\n");
		if (list->type == TYPE_COMMENT)
			printf("  -> (COMMENT)\n");
		if (list->type > 11)
			printf("  -> (INSTRUCTION) %d\n", list->type);
		if (list->type == TYPE_VIRGULE)
			printf("  -> (SEPARATEUR ' , ')\n");
		if (list->type == TYPE_LABEL_DEFINITION)
			printf("  -> (DEFINITION LABEL)\n");
		if (list->type == TYPE_DIRECT)
			printf("  -> (PARAMETRE DIRECT)\n");
		if (list->type == TYPE_INDEX)
			printf("  -> (PARAMETRE INDEX)\n");
		if (list->type == TYPE_REGISTRE)
			printf("  -> (PARAMETRE REGISTRE)\n");
		if (list->type == TYPE_UNKNOWN)
			printf("  -> (ELEMENT INCONNU)\n");
		if (list->type == TYPE_LABEL)
			printf("  -> (APPEL LABEL)\n");
		if (list->type == TYPE_DIRECT_2)
			printf("  -> (DIRECT 2)\n");
		if (list->type == TYPE_DIRECT_4)
			printf("  -> (DIRECT 4)\n");
		list = list->next;
	}
}

int main(int argc, char **argv)
{
	t_env *env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (-1);
	env->list = NULL;
	if (argc > 1)
	{
		env->fd = open(argv[1], O_RDONLY);
		while (get_char(env->fd, env->buffer) > 0)
		{
			if (env->buffer[0] == '.' && !get_command(env))
			{
				ft_putendl("malloc error");
				break ;
			}
			if (env->buffer[0] == '"' && !get_str(env))
			{
				ft_putendl("malloc error");
				break ;
			}
			if (env->buffer[0] == '#' && !get_comment(env))
			{
				ft_putendl("malloc error");
				break ;
			}
			if (!is_blank(env->buffer[0]) && !get_instruction(env))
			{
				ft_putendl("malloc error");
				break ;
			}
		}
		print_lst(env->list);
	}
  return (exit_gc(env, 0));
}

// int my_destructor(void) __attribute__((destructor));
// int my_destructor(void) /* This function is called after main() */
// {                       /* completes or after exit() is called. */
//     while (2) ;
// }
