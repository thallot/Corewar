/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_two.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:18:27 by thallot           #+#    #+#             */
/*   Updated: 2019/11/29 11:28:57 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Verifie si l'instruction LD et ses parametres sont valides
*/

void	is_valid_ld(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || (env->list->type != TYPE_DIRECT
		&& env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "ld", 1);
	is_valid_param(env, "ld");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "ld", 1, 2);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "ld", 2);
	is_valid_param(env, "ld");
	env->size += get_size(env);
}

/*
** Verifie si l'instruction ST et ses parametres sont valides
*/

void	is_valid_st(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "st", 1);
	env->size += get_size(env);
	is_valid_param(env, "st");
	is_valid_separator(env, "st", 1, 2);
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "st", 2);
	env->size += get_size(env);
	is_valid_param(env, "st");
}

/*
** Verifie si l'instruction ADD et ses parametres sont valides
*/

void	is_valid_add(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "add", 1);
	env->size += get_size(env);
	is_valid_param(env, "add");
	is_valid_separator(env, "add", 1, 2);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "add", 2);
	env->size += get_size(env);
	is_valid_param(env, "add");
	is_valid_separator(env, "add", 2, 3);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "add", 3);
	env->size += get_size(env);
	is_valid_param(env, "add");
}

/*
** Verifie si l'instruction SUB et ses parametres sont valides
*/

void	is_valid_sub(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "sub", 1);
	env->size += get_size(env);
	is_valid_param(env, "sub");
	is_valid_separator(env, "sub", 1, 2);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "sub", 2);
	env->size += get_size(env);
	is_valid_param(env, "sub");
	is_valid_separator(env, "sub", 2, 3);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "sub", 3);
	env->size += get_size(env);
	is_valid_param(env, "sub");
}

/*
** Verifie si l'instruction AND et ses parametres sont valide
*/

void	is_valid_and(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "and", 1);
	is_valid_param(env, "and");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "and", 1, 2);
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "and", 2);
	is_valid_param(env, "and");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "and", 2, 3);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "and", 3);
	env->size += get_size(env);
	is_valid_param(env, "and");
}
