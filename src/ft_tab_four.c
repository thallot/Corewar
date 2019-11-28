/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_four.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:08:43 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/13 17:27:10 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Verifie si l'instruction fork possede les bons parametres,
** et en bon nombre
*/

void	is_valid_fork(t_env *env)
{
	env->size += T_INSTRUCTION;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_DIRECT)
		print_error(env, "fork", 1);
	is_valid_param(env, "fork");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
}

/*
** Verifie si l'instruction aff possede les bons parametres,
** et en bon nombre
*/

void	is_valid_aff(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "aff", 1);
	env->size += get_size(env);
	is_valid_param(env, "aff");
}

/*
** Verifie si l'instruction lfork possede les bons parametres,
** et en bon nombre
*/

void	is_valid_lfork(t_env *env)
{
	env->size += T_INSTRUCTION;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_DIRECT)
		print_error(env, "lfork", 1);
	is_valid_param(env, "lfork");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
}

/*
** Verifie si l'instruction lldi possede les bons parametres,
** et en bon nombre
*/

void	is_valid_lldi(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT
		&& env->list->type != TYPE_LABEL))
		print_error(env, "lldi", 1);
	is_valid_param(env, "lldi");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "lldi", 1, 2);
	if (!env->list || (env->list->type != TYPE_REGISTRE
			&& env->list->type != TYPE_DIRECT))
		print_error(env, "lldi", 2);
	is_valid_param(env, "lldi");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "lldi", 2, 3);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "lldi", 3);
	env->size += get_size(env);
	is_valid_param(env, "lldi");
}

/*
** Verifie si l'instruction lld possede les bons parametres,
** et en bon nombre
*/

void	is_valid_lld(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || (env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL))
		print_error(env, "lld", 1);
	is_valid_param(env, "lld");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "lld", 1, 2);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "lld", 2);
	env->size += get_size(env);
	is_valid_param(env, "lld");
}
