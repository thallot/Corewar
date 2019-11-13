/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 13:53:40 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/13 15:31:04 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"
#include <stdlib.h>

/*
** copie d'un memalloc classique + exit proprement en cas d'echec malloc
** + ajoute le pointeur malloc au garbage collector
*/

void	*ft_memalloc_gc(size_t size, t_env *env)
{
	char *ptr;

	if (!(ptr = (char *)malloc(sizeof(*ptr) * size)))
		exit(exit_gc(env, -1));
	ft_bzero(ptr, size);
	add_list_gc(env, ptr);
	return (ptr);
}

/*
** copie d'un strdup classique + exit proprement en cas d'echec malloc
** + ajoute le pointeur malloc au garbage collector
*/

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

/*
** copie d'un strjoin classique + exit proprement en cas d'echec malloc
** + ajoute le pointeur malloc au garbage collector
*/

char	*ft_strjoin_gc(char *s1, char const *s2, t_env *env)
{
	char	*str;
	size_t	size;

	str = NULL;
	if (s2)
	{
		if (!s1)
		{
			if (!(s1 = (char *)ft_memalloc(sizeof(char))))
				exit(exit_gc(env, -1));
			add_list_gc(env, s1);
		}
		size = ft_strlen(s1) + ft_strlen(s2);
		if (!(str = (char *)ft_memalloc(sizeof(char) * size + 1)))
			exit(exit_gc(env, -1));
		str = ft_strcat(str, s1);
		str = ft_strcat(str, s2);
		str[size] = '\0';
		add_list_gc(env, str);
	}
	return (str);
}

/*
** copie d'un strndup classique + exit proprement en cas d'echec malloc
** + ajoute le pointeur malloc au garbage collector
*/

char	*ft_strndup_gc(t_env *env, const char *s1, size_t n)
{
	size_t	i;
	char	*dest;

	if (!(dest = (char *)malloc(sizeof(*dest) * n + 1)))
		exit(exit_gc(env, -1));
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	add_list_gc(env, dest);
	return (dest);
}
