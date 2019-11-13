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

void	is_valid_command(t_env *env)
{
	if (!ft_strcmp(env->list->name, NAME_CMD_STRING)
			|| !ft_strcmp(env->list->name, COMMENT_CMD_STRING))
		return ;
	printf("Commande inconnue [%s]\n", env->list->name);
	exit(exit_gc(env, 1));
}

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
	printf("Chaine de caractere mal formatée [%s]\n", env->list->name);
	exit(exit_gc(env, 1));
}

void	is_valid_label_definition(t_env *env)
{
	int		i;
	int		size;
	char	c;
	t_lst	*current;

	i = -1;
	size = ft_strlen(env->list->name) - 1;
	while (env->list->name[++i])
	{
		c = env->list->name[i];
		if (!((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
				&& !(i == size && c == ':'))
		{
			printf("Label [%s], caractere invalide : %c\n", env->list->name, c);
			exit(exit_gc(env, 1));
		}
	}
	current = env->label;
	while (current)
	{
		if (!ft_strcmp(current->name, env->list->name))
			current->type = env->size;
		current = current->next;
	}
}

void	is_valid_registre(t_env *env)
{
	int i;

	i = ft_atoi(&(env->list->name)[1]);
	if (i >= 0 && i <= 16)
		return ;
	printf("Erreur de formatage du registre [%s]\n", env->list->name);
	exit(exit_gc(env, 1));
}

void	is_valid_live(t_env *env)
{
	env->size += T_INSTRUCTION;
	env->list = env->list->next;
	if (env->list->type != TYPE_DIRECT)
		print_error(env, "live", 1);
	is_valid_param(env);
	env->list->type = TYPE_DIRECT_4;
	env->size += get_size(env);
}
