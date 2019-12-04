/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:56:57 by thallot           #+#    #+#             */
/*   Updated: 2019/11/29 15:47:54 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "../include/asm.h"

/*
** Reverse les bytes d'une variable
*/

void	ft_memrev(void *mask, size_t size)
{
	size_t	i;
	size_t	j;
	char	tmp;
	char	*c;

	c = (char*)mask;
	i = 0;
	j = size - 1;
	while (i < j)
	{
		tmp = c[i];
		c[i] = c[j];
		c[j] = tmp;
		i++;
		j--;
	}
}

/*
** Skip Comment with opt = 0
** Skip Comment and separator and label definition with opt != 0
*/

void	zap_all(t_env *env, int opt)
{
	if (opt == 0)
	{
		while (env->list->type == TYPE_COMMENT
		|| env->list->type == TYPE_NEWLINE)
			env->list = env->list->next;
	}
	else
	{
		while (env->list && (env->list->type == TYPE_VIRGULE
		|| env->list->type == TYPE_COMMENT
		|| env->list->type == TYPE_NEWLINE
		|| env->list->type == TYPE_LABEL_DEFINITION))
			env->list = env->list->next;
	}
}

/*
** Boucle qui effectue un | binaire sur l'int OCP,
** en fonction du parametre de env->list
** Return l'OCP
*/

int		loop_ocp(t_env *env, int offset)
{
	int i;
	int ocp;

	i = 0;
	ocp = 0;
	while (i < offset && env->list)
	{
		if (env->list->type == TYPE_VIRGULE)
			env->list = env->list->next;
		if (env->list->type == TYPE_REGISTRE)
			ocp = ocp | REG_CODE;
		else if (env->list->type == TYPE_DIRECT_2
		|| env->list->type == TYPE_DIRECT_4)
			ocp = ocp | DIR_CODE;
		else
			ocp = ocp | IND_CODE;
		ocp = ocp << 2;
		env->list = env->list->next;
		i++;
	}
	if (offset == 2)
		ocp = ocp << 2;
	return (ocp);
}

/*
** Genere un OCP en fonction des parametre de l'instruction
*/

int		generate_ocp(t_env *env)
{
	t_lst	*head;
	int		offset;
	int		ocp;

	head = env->list;
	if (env->list->type == TYPE_AFF)
		return (64);
	if (env->list->type == TYPE_LD
	|| env->list->type == TYPE_ST
	|| env->list->type == TYPE_LLD)
		offset = 2;
	else
		offset = 3;
	env->list = env->list->next;
	ocp = loop_ocp(env, offset);
	env->list = head;
	return (ocp);
}

/*
** Recherche un label dans la liste de label,
** et retourne son index (en octet)
*/

int		looking_for_label(t_env *env, char *to_find)
{
	t_lst *current;

	current = env->label;
	while (current)
	{
		if (ft_strcmp(to_find, current->name) == 0)
			return (current->type);
		current = current->next;
	}
	return (0);
}
