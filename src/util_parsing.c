/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:55:19 by thallot           #+#    #+#             */
/*   Updated: 2019/11/13 15:59:41 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

int		get_size(t_env *env)
{
	if (env->list->type == TYPE_REGISTRE
	|| (env->list->type >= TYPE_INSTRUCTION_LIVE
	&& env->list->type <= TYPE_INSTRUCTION_AFF))
		return (1);
	if (env->list->type == TYPE_DIRECT_2
	|| env->list->type == TYPE_INDEX
	|| env->list->type == TYPE_LABEL_DEFINITION
	|| env->list->type == TYPE_LABEL)
		return (2);
	if (env->list->type == TYPE_DIRECT_4)
		return (4);
	printf("Mauvais type de parametre dans get_size sur %s (type : %d)", \
	env->list->name, env->list->type);
	exit(exit_gc(env, 1));
}

void	print_error(t_env *env, char *instr, int nb)
{
	printf("Erreur de type de parametre pour l'instruction %s, \
	parametre %d : [%s]\n", instr, nb, env->list->name);
	exit(exit_gc(env, 1));
}

int		is_valid_separator(t_env *env, char *instr, int one, int two)
{
	if (env->list->type != TYPE_VIRGULE)
	{
		printf("Erreur de formatage pour l'instruction %s, \
		pas de separateur dans le %de et le %de parametre", instr, one, two);
		exit(exit_gc(env, 1));
	}
	env->list = env->list->next;
	return (1);
}

int		is_valid_param(t_env *env)
{
	if (((env->list->type == TYPE_DIRECT
	&& env->list->name[1] == ':') || env->list->type == TYPE_LABEL))
		is_valid_label_call(env);
	if (env->list->type == TYPE_REGISTRE)
		is_valid_registre(env);
	return (1);
}

void	is_valid_label_call(t_env *env)
{
	int		i;
	t_lst	*head;

	i = 0;
	if (env->list->name[i] == '%')
		i++;
	if (env->list->name[i] == ':')
		i++;
	head = env->label;
	while (env->label)
	{
		if (!ft_strcmp(env->label->name, i + env->list->name))
		{
			env->label = head;
			return ;
		}
		env->label = env->label->next;
	}
	printf("Le label %s n'existe pas\n", i + env->list->name);
	exit(exit_gc(env, 1));
}