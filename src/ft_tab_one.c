/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tab_one.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:04:57 by thallot           #+#    #+#             */
/*   Updated: 2019/11/13 15:28:46 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Verifie si la commande est valide (nom ou commentaire)
*/

void	is_valid_command(t_env *env)
{
	if (!ft_strcmp(env->list->name, NAME_CMD_STRING)
			|| !ft_strcmp(env->list->name, COMMENT_CMD_STRING))
		return ;
	ft_printf("Erreur : Commande inconnue [%s] (.name || .comment)\n"
	, env->list->name);
	exit(exit_gc(env, 1));
}

/*
** Verifie si la chaine de caractere commence,
** et finis par le caractere "
*/

void	is_valid_str(t_env *env)
{
	int		size;
	char	*name;

	name = env->list->name;
	size = ft_strlen(env->list->name) - 1;
	if (env->list->name[0] == '"' && env->list->name[size] == '"')
	{
		name = ft_memmove(name, env->list->name + 1, size);
		env->list->name[size] = '\0';
		env->list->name[size - 1] = '\0';
		return ;
	}
	ft_printf("Erreur : Chaine de caractere -> [%s] est mal formatée\n"
	, env->list->name);
	exit(exit_gc(env, 1));
}

/*
** Verifie que le label est composé uniquement de caractere
** disponible dans LABEL_CHARS, et que le label existe
*/

void	is_valid_label_definition(t_env *env)
{
	int		i;
	int		size;
	char	c;
	t_lst	*current;

	i = -1;
	size = ft_strlen(env->list->name) - 1;
	if (size == -1)
		exit_label_def(env, 0, 0);
	if (env->list->name[size - 1] == ':')
		exit_label_def(env, 1, 0);
	while (env->list->name[++i])
	{
		c = env->list->name[i];
		if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_'))
			exit_label_def(env, 2, c);
	}
	current = env->label;
	while (current)
	{
		if (!ft_strcmp(current->name, env->list->name))
			current->type = env->size;
		current = current->next;
	}
}

/*
** Verifie que le registre est compris entre 0 et 16
*/

void	is_valid_registre(t_env *env, char *instruction)
{
	int i;

	if (!ft_isnumber(&(env->list->name)[1], 0))
		return ;
	i = ft_atoi(&(env->list->name)[1]);
	if ((i >= 1 && i <= 16))
		return ;
	ft_printf("Erreur : instruction %s -> [%s] doit etre 1-16\n"
	, instruction, env->list->name);
	exit(exit_gc(env, 1));
}

/*
** Verifie si l'instruction live possede les bons parametres,
** et en bon nombre
*/

void	is_valid_live(t_env *env)
{
	env->size += T_INSTRUCTION;
	env->list = env->list->next;
	if (!env->list || env->list->type != TYPE_DIRECT)
		print_error(env, "live", 1);
	is_valid_param(env, "live");
	env->list->type = TYPE_DIRECT_4;
	env->size += get_size(env);
}
