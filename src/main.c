/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:05:30 by thallot           #+#    #+#             */
/*   Updated: 2019/11/13 15:54:05 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

int		is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
	|| c == '\f' | c == '\0')
		return (1);
	return (0);
}

int		is_separator(char c)
{
	if (c == ',')
		return (1);
	return (0);
}

void	print_lst(t_lst *list)
{
	while (list)
	{
		printf("%-15s", list->name);
		printf("SIZE : %d\n", list->type);
		list = list->next;
	}
}

void	check_error_main(t_env *env, int argc, char **argv, int opt)
{
	if (opt == 0)
	{
		if (argc != 2)
		{
			printf("Wrong params number\n");
			exit(exit_gc(env, 1));
		}
		if ((env->fd_s = open(argv[1], O_RDONLY)) <= 0)
		{
			printf(".S FILE DOES NOT EXIST\n");
			exit(exit_gc(env, 1));
		}
		if (read(env->fd_s, 0, 0) < 0)
		{
			printf("Not a valid file\n");
			exit(exit_gc(env, 1));
		}
	}
	else if (!env->list)
	{
		printf("Not a valid file\n");
		exit(exit_gc(env, 1));
	}
}

int		main(int argc, char **argv)
{
	t_env *env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (-1);
	parsing_file_s(env, argv[1]);
	check_error_main(env, argc, argv, 0);
	while (get_char(env->fd_s, env->buffer) > 0)
	{
		if (env->buffer[0] == '.')
			get_command(env);
		if (env->buffer[0] == '"')
			get_str(env);
		if (env->buffer[0] == '#')
			get_comment(env);
		if (!is_blank(env->buffer[0]))
			get_instruction(env);
	}
	check_error_main(env, argc, argv, 1);
	loop_parser(env);
	w_header(env);
	w_core(env);
	printf("Writing output program to %s.cor\n", env->file_name);
	return (exit_gc(env, 0));
}

/*
** int my_destructor(void) __attribute__((destructor));
** int my_destructor(void)
** {
**     while (2) ;
** }
*/
