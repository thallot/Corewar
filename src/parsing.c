/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 10:25:25 by thallot           #+#    #+#             */
/*   Updated: 2019/11/06 10:25:26 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

int is_valid_command(t_env *env)
{
  if (!ft_strcmp(env->list->name, NAME_CMD_STRING)
  || !ft_strcmp(env->list->name, COMMENT_CMD_STRING))
    return (1);
  return (0);
}

int is_valid_str(t_env *env)
{
  int size;

  size = ft_strlen(env->list->name) - 1;
  if (env->list->name[0] == '"' && env->list->name[size] == '"')
    return (1);
  return (0);
}

int is_valid_label(t_env *env)
{
  int i;
  int size;
  char c;

  i = 0;
  size = ft_strlen(env->list->name) - 1;
  while (env->list->name[i])
  {
    c = env->list->name[i];
    if ((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || c == '_')
      i++;
    else
    {
      if (i == size && c == ':')
        return (1);
      printf("Erreur de formatage du label [%s], caractere invalide : %c", env->list->name, c);
      return (0);
    }
  }
  return (1);
}

// int is_valid_registre(t_env *env)
// {
//   int i;
//
//
// }

int is_valid_live(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT_4)
    return (0);
  return (1);
}

// void *create_tab_function(t_env *env)
// {
//   int (*check_instruction[27])(t_env*);
//
//   (void)env;
//   check_instruction[0] = &is_valid_live;
//   return (check_instruction);
// }

int loop_parser(t_env *env)
{
  while (env->list)
  {
    if (env->list->type == TYPE_LABEL_DEFINITION)
      printf(" VALID LABEL : %d (LABEL : %s)\n", is_valid_label(env), env->list->name);
    if (env->list->type == TYPE_COMMAND)
      printf(" VALID COMMAND : %d (COMMAND : %s)\n", is_valid_command(env), env->list->name);
    if (env->list->type == TYPE_STR)
      printf(" VALID STR : %d (STR : %s)\n", is_valid_str(env), env->list->name);
    if (env->list->type == TYPE_INSTRUCTION_LIVE)
      printf(" VALID LIVE : %d (PARAM : %s | type %d)\n", is_valid_live(env), env->list->name, env->list->type);
    env->list = env->list->next;
  }
  return (1);
}
