/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   byte_ope.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 09:56:57 by thallot           #+#    #+#             */
/*   Updated: 2019/11/08 09:56:58 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "../include/asm.h"

void    ft_memrev(void *mask, size_t size)
{
    size_t    i;
    size_t    j;
    char    tmp;
    char    *c;
    c = (char*)mask;
    i =  0;
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

void	w_header(t_env *env)
{
	int		fd;
	int		magic;
	char	name[129];
	char	comment[2049];
	int		i;

	i = -1;
	magic = 15369203;
	ft_bzero(name, 129);
	ft_bzero(comment, 2049);
	env->list = env->list->next;
	ft_strcpy(name, env->list->name);
	env->list = env->list->next;
	env->list = env->list->next;
	ft_strcpy(comment, env->list->name);
	ft_memrev(&magic, 4);
	fd = open("test.cor", O_WRONLY);
	write(fd, &magic, 4);
	lseek(fd, SEEK_CUR, 4);
	write(fd, name, 129);
	lseek(fd, SEEK_CUR, 129);
	write(fd, comment, 2049);
}
