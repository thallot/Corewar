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

/*
** Return la taille en octet de l'element actuellement pointé
** par le pointeur sur liste du lexeur (env->list)
** Gestion d'erreur si l'element n'est pas de type parametre
*/

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
	ft_printf("Mauvais type de parametre dans get_size sur %s (type : %d)", \
	env->list->name, env->list->type);
	exit(exit_gc(env, 1));
}

/*
** Affiche sur la sortie standard un message d'erreur correspondant a
** l'erreur rencontrée
** Exit ensuite le programme proprement
*/

void	print_error(t_env *env, char *instr, int nb)
{
	if (nb == 0)
		ft_printf("Erreur de formatage de parametre pour l'instruction %s, \
	parametre : [%s] devrait etre numerique\n", instr, env->list->name);
	else
		ft_printf("Erreur de type de parametre pour l'instruction %s, \
	parametre %d : [%s]\n", instr, nb, env->list->name);
	exit(exit_gc(env, 1));
}

/*
** Idenfifie l'element comment etant le separateur ','
** si l'element ne correspond pas, exit le programme proprement
*/

int		is_valid_separator(t_env *env, char *instr, int one, int two)
{
	if (env->list->type != TYPE_VIRGULE)
	{
		ft_printf("Erreur de formatage pour l'instruction %s, \
		pas de separateur dans le %de et le %de parametre", instr, one, two);
		exit(exit_gc(env, 1));
	}
	env->list = env->list->next;
	return (1);
}

/*
** Verifie la validite de l'element dans le cas d'un DIRECT (label) ||
** INDIRECT (label) || REGISTRE || DIRECT
*/

int		is_valid_param(t_env *env, char *instruction)
{
	if (((env->list->type == TYPE_DIRECT
	&& env->list->name[1] == ':') || env->list->type == TYPE_LABEL))
		is_valid_label_call(env);
	else if (env->list->type == TYPE_DIRECT)
		if (!ft_isnumber(env->list->name + 1, 0))
			print_error(env, instruction, 0);
	if (env->list->type == TYPE_REGISTRE)
		is_valid_registre(env);
	
	return (1);
}

/*
** Verifie si l'element DIRECT (label) || INDIRECT (label)
** fait reference a un label existant parmis la liste de label
** identifiée précédemment, en cas d'erreur, exit proprement
*/

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
	ft_printf("Le label %s n'existe pas\n", i + env->list->name);
	exit(exit_gc(env, 1));
}
