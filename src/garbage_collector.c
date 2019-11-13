/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:04:27 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/13 13:59:06 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"
#include <stdlib.h>

/*
** Traverse la liste garbage collector et libere tous les nodes
*/

void	del_garbage_collector(t_env *env)
{
	t_gc *current;
	t_gc *next;

	if (!(env->garbage_collector))
		return ;
	current = env->garbage_collector;
	while (current)
	{
		next = current->next;
		ft_memdel((void**)&(current->data));
		ft_memdel((void**)&current);
		current = next;
	}
}

/*
** Fonction a appeler dans tout appel à exit()
** Libere le garbage collector ainsi que la structure d'environnement
*/

int		exit_gc(t_env *env, int ret)
{
	if (ret == -1)
		ft_putendl("Malloc error");
	del_garbage_collector(env);
	ft_memdel((void**)&env);
	return (ret);
}

/*
** Ajoute un maillon a la liste garbage collector
** Stock le pointeur sur une zone memoire fraichement alloue dans le node
*/

t_gc	*add_list_gc(t_env *env, void *data)
{
	t_gc *new;

	if (!(new = (t_gc *)malloc((sizeof(t_gc)))))
		exit(exit_gc(env, -1));
	new->data = data;
	new->next = NULL;
	if (!(env->garbage_collector))
		env->garbage_collector = new;
	else
	{
		new->next = env->garbage_collector;
		env->garbage_collector = new;
	}
	return (env->garbage_collector);
}
