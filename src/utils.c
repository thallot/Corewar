/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:51:15 by thallot           #+#    #+#             */
/*   Updated: 2019/11/13 15:51:16 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Retourne le type d'un element du lexeur en fonction de
** son premier caractere
*/

int		get_type_param(t_env *env)
{
	int type;

	if (env->buffer[0] == '%')
		type = TYPE_DIRECT;
	else if (ft_isdigit(env->buffer[0]))
		type = TYPE_INDEX;
	else if (env->buffer[0] == 'r')
		type = TYPE_REGISTRE;
	else if (env->buffer[0] == ':')
		type = TYPE_LABEL;
	else
		type = TYPE_UNKNOWN;
	return (type);
}

/*
** Ajoute un element dans la liste du lexeur,
** avec son type et sa valeur (name)
*/

void	add_elem(t_env *env, int type, char *instruction, char last_char)
{
	int instruction_type;

	if (last_char == ':')
	{
		add_list(&(env->list), instruction, TYPE_LABEL_DEFINITION, env);
		instruction[ft_strlen(instruction) - 1] = '\0';
		add_list(&(env->label), instruction, TYPE_LABEL_DEFINITION, env);
	}
	else if (instruction)
	{
		if ((instruction_type = is_instruction(instruction)))
			type = instruction_type;
		else if (ft_isnumber(instruction, 1))
			type = TYPE_INDEX;
		add_list(&(env->list), instruction, type, env);
	}
	if (env->buffer[0] == ',')
		add_list(&(env->list), ",", TYPE_VIRGULE, env);
	if (env->buffer[0] == '\n')
		add_list(&(env->list), "NL", TYPE_NEWLINE, env);
}

/*
** Return le type d'instruction en fonction de la string passée
** en paramètre
*/

int		is_instruction(char *str)
{
	if (!ft_strcmp("live", str))
		return (TYPE_LIVE);
	else if (!ft_strcmp("ld", str))
		return (TYPE_LD);
	else if (!ft_strcmp("st", str))
		return (TYPE_ST);
	else if (!ft_strcmp("add", str))
		return (TYPE_ADD);
	else if (!ft_strcmp("sub", str))
		return (TYPE_SUB);
	else if (!ft_strcmp("and", str))
		return (TYPE_AND);
	else if (!ft_strcmp("or", str))
		return (TYPE_OR);
	else if (!ft_strcmp("xor", str))
		return (TYPE_XOR);
	return (is_instruction_next(str));
}

/*
** Suite de la fonction ci-dessus
*/

int		is_instruction_next(char *str)
{
	if (!ft_strcmp("zjmp", str))
		return (TYPE_ZJMP);
	else if (!ft_strcmp("ldi", str))
		return (TYPE_LDI);
	else if (!ft_strcmp("sti", str))
		return (TYPE_STI);
	else if (!ft_strcmp("fork", str))
		return (TYPE_FORK);
	else if (!ft_strcmp("lld", str))
		return (TYPE_LLD);
	else if (!ft_strcmp("lldi", str))
		return (TYPE_LLDI);
	else if (!ft_strcmp("lfork", str))
		return (TYPE_LFORK);
	else if (!ft_strcmp("aff", str))
		return (TYPE_AFF);
	return (0);
}

/*
** Ajoute un nouvel élément à la liste du lexeur,
** y stocke la chaine de caractères passée en paramètre
*/

t_lst	*add_list(t_lst **list, char *name, int type, t_env *env)
{
	t_lst *new;
	t_lst **head;

	head = list;
	new = (t_lst *)ft_memalloc_gc((sizeof(t_lst)), env);
	new->name = name;
	new->type = type;
	new->next = NULL;
	if (!(*list))
		*list = new;
	else
	{
		while ((*list)->next)
			list = &(*list)->next;
		(*list)->next = new;
	}
	list = head;
	return (*head);
}
