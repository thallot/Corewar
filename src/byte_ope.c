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

void zap_comment(t_env *env)
{
  while (env->list->type == TYPE_COMMENT)
    env->list = env->list->next;
}

void	w_header(t_env *env)
{
	int		fd;
	int		magic;
	char	name[132];
	char	comment[2052];
	int		i;
  int size;

	i = -1;
  printf("SIZE : %d\n", env->size);
  size = env->size;
	magic = 15369203;
	ft_bzero(name, 132);
	ft_bzero(comment, 2052);
  zap_comment(env);
  if (ft_strcmp(env->list->name, NAME_CMD_STRING))
  {
    printf("Le nom du champions n'est pas la 1ere commande\n");
    exit(exit_gc(env, 1));
  }
  zap_comment(env);
  env->list = env->list->next;
  ft_strcpy(name, env->list->name);
  env->list = env->list->next;
  if (ft_strcmp(env->list->name, COMMENT_CMD_STRING))
  {
    printf("Le commentaire du champions n'est pas la 2e commande (%s)\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  zap_comment(env);
	env->list = env->list->next;
	ft_strcpy(comment, env->list->name);
	ft_memrev(&magic, 4);
  ft_memrev(&size, 4);
	fd = open("test.cor", O_TRUNC | O_RDWR | O_CREAT, 0777);
  printf("FD : %d\n", fd);
	write(fd, &magic, 4);
	lseek(fd, SEEK_CUR, 4);
	write(fd, name, 132);
  lseek(fd, SEEK_CUR, 132);
  write(fd, &size, 4);
	lseek(fd, SEEK_CUR, 4);
	write(fd, comment, 2052);
}
