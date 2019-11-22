/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:25:25 by thallot           #+#    #+#             */
/*   Updated: 2019/11/13 15:57:52 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Initialise le tableau de pointeur sur fonction
*/

void	init_parsing_tab(t_env *env)
{
	env->parsing[TYPE_COMMAND] = is_valid_command;
	env->parsing[TYPE_STR] = is_valid_str;
	env->parsing[TYPE_LABEL_DEFINITION] = is_valid_label_definition;
	env->parsing[TYPE_INSTRUCTION_LIVE] = is_valid_live;
	env->parsing[TYPE_INSTRUCTION_LD] = is_valid_ld;
	env->parsing[TYPE_INSTRUCTION_ST] = is_valid_st;
	env->parsing[TYPE_INSTRUCTION_ADD] = is_valid_add;
	env->parsing[TYPE_INSTRUCTION_SUB] = is_valid_sub;
	env->parsing[TYPE_INSTRUCTION_AND] = is_valid_and;
	env->parsing[TYPE_INSTRUCTION_OR] = is_valid_or;
	env->parsing[TYPE_INSTRUCTION_XOR] = is_valid_xor;
	env->parsing[TYPE_INSTRUCTION_ZJMP] = is_valid_zjmp;
	env->parsing[TYPE_INSTRUCTION_LDI] = is_valid_ldi;
	env->parsing[TYPE_INSTRUCTION_STI] = is_valid_sti;
	env->parsing[TYPE_INSTRUCTION_FORK] = is_valid_fork;
	env->parsing[TYPE_INSTRUCTION_LLD] = is_valid_lld;
	env->parsing[TYPE_INSTRUCTION_LLDI] = is_valid_lldi;
	env->parsing[TYPE_INSTRUCTION_LFORK] = is_valid_lfork;
	env->parsing[TYPE_INSTRUCTION_AFF] = is_valid_aff;
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
		if (env->list->type >= TYPE_INSTRUCTION_LIVE
		&& env->list->type <= TYPE_LABEL_DEFINITION)
			env->parsing[env->list->type](env);
		else if (env->list->type != TYPE_COMMENT)
		{
			ft_printf("Erreur : element inconnu -> [%s]\n", env->list->name);
			exit(exit_gc(env, 1));
		}
		env->list = env->list->next;
	}
	env->list = head;
	return (1);
}
