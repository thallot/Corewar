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
  if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' | c == '\0')
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
		printf("SIZE : %d\n", list->type);
		list = list->next;
	}
}

int main(int argc, char **argv)
{
	t_env *env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (-1);
	parsing_file_s(env, argv[1]);
	if (argc > 1)
	{
		if ((env->fd_s = open(argv[1], O_RDONLY)) == -1)
		{
			printf(".S FILE DOES NOT EXIST\n");
			exit(exit_gc(env, 1));
		}
		while (get_char(env->fd_s, env->buffer) > 0)
		{
			if (env->buffer[0] == '.' && !get_command(env))
				exit(exit_gc(env, -1));
			if (env->buffer[0] == '"' && !get_str(env))
				exit(exit_gc(env, -1));
			if (env->buffer[0] == '#' && !get_comment(env))
				exit(exit_gc(env, -1));
			if (!is_blank(env->buffer[0]) && !get_instruction(env))
				exit(exit_gc(env, -1));
		}
		loop_parser(env);
		w_header(env);
		w_core(env);
		printf("Writing output program to %s.cor\n", env->file_name);
	}
  return (exit_gc(env, 0));
}

// int my_destructor(void) __attribute__((destructor));
// int my_destructor(void) /* This function is called after main() */
// {                       /* completes or after exit() is called. */
//     while (2) ;
// }
