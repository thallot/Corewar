/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:25:25 by thallot           #+#    #+#             */
/*   Updated: 2019/11/29 11:29:41 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

void	exit_parsing_loop(t_env *env, int opt)
{
	if (opt == 1)
	{
		ft_printf("Erreur : Pas de new line après une instruction\n");
		exit(exit_gc(env, 1));
	}
	else
	{
		ft_printf("Erreur : element inconnu -> [%s]\n", env->list->name);
		exit(exit_gc(env, 1));
	}
}

void	exit_label_def(t_env *env, int opt, char c)
{
	if (opt == 0)
	{
		ft_printf("Erreur : label vide\n");
		exit(exit_gc(env, 1));
	}
	else if (opt == 1)
	{
		ft_printf("Erreur : label invalide\n");
		exit(exit_gc(env, 1));
	}
	else if (opt == 2)
	{
		ft_printf("Erreur : label %s -> caractere invalide : %c\n"
		, env->list->name, c);
		exit(exit_gc(env, 1));
	}
}

/*
** Initialise le tableau de pointeur sur fonction
*/

void	init_parsing_tab(t_env *env)
{
	env->parsing[TYPE_COMMAND] = is_valid_command;
	env->parsing[TYPE_STR] = is_valid_str;
	env->parsing[TYPE_LABEL_DEFINITION] = is_valid_label_definition;
	env->parsing[TYPE_LIVE] = is_valid_live;
	env->parsing[TYPE_LD] = is_valid_ld;
	env->parsing[TYPE_ST] = is_valid_st;
	env->parsing[TYPE_ADD] = is_valid_add;
	env->parsing[TYPE_SUB] = is_valid_sub;
	env->parsing[TYPE_AND] = is_valid_and;
	env->parsing[TYPE_OR] = is_valid_or;
	env->parsing[TYPE_XOR] = is_valid_xor;
	env->parsing[TYPE_ZJMP] = is_valid_zjmp;
	env->parsing[TYPE_LDI] = is_valid_ldi;
	env->parsing[TYPE_STI] = is_valid_sti;
	env->parsing[TYPE_FORK] = is_valid_fork;
	env->parsing[TYPE_LLD] = is_valid_lld;
	env->parsing[TYPE_LLDI] = is_valid_lldi;
	env->parsing[TYPE_LFORK] = is_valid_lfork;
	env->parsing[TYPE_AFF] = is_valid_aff;
}

/*
** Boucle principale de parsing du fichier .s
** a chaque iteration, fait appel à une fonction du tableau défini précédemment
** en fonction du type de l'element
*/

int		loop_parser(t_env *env)
{
	t_lst *head;

	head = env->list;
	init_parsing_tab(env);
	while (env->list)
	{
		if (env->list->type >= TYPE_LIVE && env->list->type <= TYPE_AFF)
		{
			env->parsing[env->list->type](env);
			env->list = env->list->next;
			if (!env->list || (env->list->type != TYPE_NEWLINE
			&& env->list->type != TYPE_COMMENT))
				exit_parsing_loop(env, 1);
		}
		else if (env->list->type >= 17 && env->list->type <= 20)
			env->parsing[env->list->type](env);
		else if (env->list->type != TYPE_COMMENT
		&& env->list->type != TYPE_NEWLINE)
			exit_parsing_loop(env, 2);
		env->list = env->list->next;
	}
	env->list = head;
	return (1);
}
