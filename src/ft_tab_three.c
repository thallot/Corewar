/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_three.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:08:32 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/13 15:20:11 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Verifie si l'instruction OR et ses parametres sont valides
*/

void	is_valid_or(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "or", 1);
	is_valid_param(env, "or");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "or", 1, 2);
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "or", 2);
	is_valid_param(env, "or");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "or", 2, 3);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "or", 3);
	env->size += get_size(env);
	is_valid_param(env, "or");
}

/*
** Verifie si l'instruction XOR et ses parametres sont valides
*/

void	is_valid_xor(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "xor", 1);
	is_valid_param(env, "or");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "xor", 1, 2);
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "xor", 2);
	is_valid_param(env, "or");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "xor", 2, 3);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "xor", 3);
	env->size += get_size(env);
	is_valid_param(env, "or");
}

/*
** Verifie si l'instruction ZJMP et ses parametres sont valides
*/

void	is_valid_zjmp(t_env *env)
{
	env->size += T_INSTRUCTION;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_DIRECT)
		print_error(env, "zjmp", 1);
	is_valid_param(env, "zjmp");
	env->list->type = TYPE_DIRECT_2;
	env->size += get_size(env);
}

/*
** Verifie si l'instruction LDI et ses parametres sont valides
*/

void	is_valid_ldi(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "ldi", 1);
	is_valid_param(env, "ldi");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "ldi", 1, 2);
	if (!env->list || (env->list->type != TYPE_DIRECT
		&& env->list->type != TYPE_REGISTRE))
		print_error(env, "ldi", 2);
	is_valid_param(env, "ldi");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "ldi", 2, 3);
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "ldi", 3);
	env->size += get_size(env);
	is_valid_param(env, "ldi");
}

/*
** Verifie si l'instruction STI et ses parametres sont valides
*/

void	is_valid_sti(t_env *env)
{
	env->size += T_INSTRUCTION + T_OCP;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_REGISTRE)
		print_error(env, "sti", 1);
	env->size += get_size(env);
	is_valid_param(env, "sti");
	is_valid_separator(env, "sti", 1, 2);
	if (!env->list || (env->list->type != TYPE_REGISTRE
		&& env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX
		&& env->list->type != TYPE_LABEL))
		print_error(env, "sti", 2);
	is_valid_param(env, "sti");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
	is_valid_separator(env, "sti", 2, 3);
	if (!env->list || (env->list->type != TYPE_DIRECT
		&& env->list->type != TYPE_REGISTRE))
		print_error(env, "sti", 3);
	is_valid_param(env, "sti");
	env->list->type = env->list->type
		== TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
	env->size += get_size(env);
}
