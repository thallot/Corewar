/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 12:04:27 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/05 12:04:38 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"
#include <stdlib.h>

void    del_garbage_collector(t_env *env)
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

int     exit_gc(t_env *env, int ret)
{
    del_garbage_collector(env);
    ft_memdel((void**)&env);
    return (ret);
}

t_gc	*add_list_gc(t_env *env, void *data)
{
	t_gc *new;

	if (!(new = (t_gc *)ft_memalloc((sizeof(t_gc)))))
		exit(exit_gc(env, -1));
	new->data = data;
	new->next = NULL;
	if (!(env->garbage_collector))
		*(&(env->garbage_collector)) = new;
	else
	{
        new->next = env->garbage_collector;
        *(&(env->garbage_collector)) = new;
	}
	return (env->garbage_collector);
}

void	*ft_memalloc_gc(size_t size, t_env *env)
{
	char *ptr;

	if (!(ptr = (char *)malloc(sizeof(*ptr) * size)))
		exit(exit_gc(env, -1));
    ft_bzero(ptr, size);
    add_list_gc(env, ptr);
	return (ptr);
}

char	*ft_strdup_gc(const char *s1, t_env *env)
{
	int		i;
	char	*dest;

	i = 0;
	while (s1[i])
		i++;
	if (!(dest = (char *)malloc(sizeof(char) * (i + 1))))
		exit(exit_gc(env, -1));
	i = -1;
	while (s1[++i])
		dest[i] = s1[i];
	dest[i] = '\0';
    add_list_gc(env, dest);
	return (dest);
}

// char    *ft_strdup_gc(const char *s1, t_env *env)
// {
//     int             i;
//     int             len;
//     char    *result;

//     i = 0;
//     len = 0;
//     while (s1[len])
//             len++;
//     if (!(result = (char*)malloc(sizeof(char) * len + 1)))
//             return (NULL);
//     while (i < len)
//     {
//             result[i] = s1[i];
//             i++;
//     }
//     result[i] = '\0';
//     add_list_gc(env, result);
//     return (result);
// }