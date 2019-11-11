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

void zap_all(t_env *env)
{
  while (env->list && (env->list->type == TYPE_VIRGULE || env->list->type == TYPE_COMMENT || env->list->type == TYPE_LABEL_DEFINITION))
    env->list = env->list->next;
}

int generate_ocp(t_env *env)
{
  t_lst *head;
  int offset;
  int ocp;
  int i;

  i = 0;
  ocp = 0;
  head = env->list;
  if (env->list->type == TYPE_INSTRUCTION_AFF)
    return (64);
  if (env->list->type == TYPE_INSTRUCTION_LD || env->list->type == TYPE_INSTRUCTION_ST || env->list->type == TYPE_INSTRUCTION_LLD)
    offset = 2;
  else
    offset = 3;
  env->list = env->list->next;
  while (i < offset && env->list)
  {
    if (env->list->type == TYPE_VIRGULE)
      env->list = env->list->next;
    if (env->list->type == TYPE_REGISTRE)
      ocp = ocp | REG_CODE;
    else if (env->list->type == TYPE_DIRECT_2 || env->list->type == TYPE_DIRECT_4 ||env->list->type == TYPE_INDEX || env->list->type == TYPE_LABEL)
      ocp = ocp | DIR_CODE;
    else
      ocp = ocp | IND_CODE;
    ocp = ocp << 2;
    env->list = env->list->next;
    i++;
  }
  if (offset == 2)
    ocp = ocp << 2;
  env->list = head;
  return (ocp);
}

int   looking_for_label(t_env *env, char *to_find)
{
  t_lst *current;

  current = env->label;
  while (current)
  {
    if (ft_strcmp(to_find, current->name) == 0)
    {
      printf("found the right label: %s\n", current->name);
      return (current->type);
    }
    current = current->next;
  }
  return (0);
}

void	w_header(t_env *env)
{
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
	env->fd_cor = open(ft_strcat(env->file_name, ".cor"), O_TRUNC | O_RDWR | O_CREAT, 0777);
  printf("FD : %d\n", env->fd_cor);
	write(env->fd_cor, &magic, 4);
	write(env->fd_cor, name, 132);
  write(env->fd_cor, &size, 4);
	write(env->fd_cor, comment, 2052);
  env->list = env->list->next;

  int ocp;
  int op;
  int octet;
  int cpt_octet;
  int cpt_instr;
  int label_index;

  cpt_octet = 0;
  // cpt_octet == compteur de la taille totale depuis le PC
  while (env->list)
  {
    zap_all(env);
    if (!env->list)
      break ;
    //octet == la taille totale de l'element que nous somme entrain d'analyser : peut etre == 1/2/4
    octet = get_size(env);
    //on incremente la taille totale depuis le PC
    cpt_octet += octet;
    // Si le type est une instruction valide ->
    if (env->list->type == TYPE_INDEX)
       printf("INDEX FOUND\n");
    if (env->list->type >= 1 && env->list->type <= 16)
    {
      //on stock son index depuis CP dans cpt_instr
      cpt_instr = cpt_octet;
      //on ecrit l'instruction dans la memoire (toutjours sur 1 octet)
      write(env->fd_cor, &(env->list)->type, 1);
      if (env->list->type != TYPE_INSTRUCTION_ZJMP && env->list->type != TYPE_INSTRUCTION_LIVE && env->list->type != TYPE_INSTRUCTION_FORK && env->list->type != TYPE_INSTRUCTION_LFORK)
      {
        ocp = generate_ocp(env);
        write(env->fd_cor, &ocp, octet);
      }
    }
    else
    {
      if (env->list->type == TYPE_DIRECT_2)
      {
        //si on rencontre un direct_2 qui fait reference a un label
        if (env->list->name[1] == ':')
        {
          // on parcours grace a looking_for_label notre liste de label et on recupere l'index du label en question
          label_index = looking_for_label(env, env->list->name + 2);
          // if (label_index > cpt_instr)
            op = label_index - cpt_instr;
          // else
          // {
            // il s'agit ici de trouver une facon de recupere l'index correspondant quand le label a ete declare avant l'appel
            //possible qu'on ait juste besoin de cast en unsigned short (ca devrait fonctionner, mais la si je change op en unsigned short, ca abort)
            // op = 65535 - (env->size - (cpt_instr - label_index));
          // }
          printf("op = %d, env->list->name + 2 = %s, label_index = %d, cpt_instr = %d, size  = %d\n", op, env->list->name + 2, label_index, cpt_instr, env->size);
        }
        else
          op = ft_atoi(&(env->list)->name[1]);
      }
      else if (env->list->type == TYPE_DIRECT_4 || env->list->type == TYPE_REGISTRE)
        op = ft_atoi(&(env->list)->name[1]);
      ft_memrev(&op, octet);
      write(env->fd_cor, &op, octet);
    }
    env->list = env->list->next;
  }
}