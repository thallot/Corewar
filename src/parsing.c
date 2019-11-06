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
  printf("Commande inconnue [%s]\n", env->list->name);
  exit(exit_gc(env, 1));
}

int is_valid_str(t_env *env)
{
  int size;

  size = ft_strlen(env->list->name) - 1;
  if (env->list->name[0] == '"' && env->list->name[size] == '"')
    return (1);
  printf("Chaine de caractere mal formatée [%s]\n", env->list->name);
  exit(exit_gc(env, 1));
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
      printf("Erreur de formatage du label [%s], caractere invalide : %c\n", env->list->name, c);
      exit(exit_gc(env, 1));
    }
  }
  return (1);
}

int is_valid_registre(t_env *env)
{
  int i;

  i = ft_atoi(&(env->list->name)[1]);
  if (i >= 0 && i <= 16)
    return (1);
  printf("Erreur de formatage du registre [%s]\n", env->list->name);
  exit(exit_gc(env, 1));
}

int is_valid_live(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT_4)
  {
    printf("Erreur de type de parametre pour l'instruction live, parametre 1 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  return (1);
}

int is_valid_ld(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT_4 && env->list->type != TYPE_INDEX)
  {
    printf("Erreur de type de parametre pour l'instruction ld, parametre 1 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction ld, pas de separateur entre le 1er et le deuxieme parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction ld, parametre 2 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_st(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction st, parametre 1 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction st, pas de separateur dans le 1er et le deuxieme parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_INDEX)
  {
    printf("Erreur de type de parametre pour l'instruction st, parametre 1 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

void  init_parsing_tab(t_env *env)
{
  env->parsing[1] = is_valid_command;
  env->parsing[2] = is_valid_str;
  env->parsing[7] = is_valid_label;
  env->parsing[9] = is_valid_registre;
  env->parsing[12] = is_valid_live;
  env->parsing[13] = is_valid_ld;
  env->parsing[14] = is_valid_st;
  env->parsing[24] = is_valid_lld;
  env->parsing[25] = is_valid_lldi;
  env->parsing[26] = is_valid_lfork;
  env->parsing[27] = is_valid_aff;
}

int loop_parser(t_env *env)
{
  init_parsing_tab(env);
  while (env->list)
  {
    if (env->list->type == TYPE_REGISTRE)
      printf(" VALID REGISTRE : %d (REGISTRE : %s)\n", is_valid_registre(env), env->list->name);
    if (env->list->type == TYPE_LABEL_DEFINITION)
      printf(" VALID LABEL : %d (LABEL : %s)\n", is_valid_label(env), env->list->name);
    if (env->list->type == TYPE_COMMAND)
      printf(" VALID COMMAND : %d (COMMAND : %s)\n", is_valid_command(env), env->list->name);
    if (env->list->type == TYPE_STR)
      printf(" VALID STR : %d (STR : %s)\n", is_valid_str(env), env->list->name);
    if (env->list->type == TYPE_INSTRUCTION_LD)
      printf(" VALID LD : %d (PARAM : %s | type %d)\n", is_valid_ld(env), env->list->name, env->list->type);
    if (env->list->type == TYPE_INSTRUCTION_ST)
      printf(" VALID ST : %d (PARAM : %s | type %d)\n", is_valid_st(env), env->list->name, env->list->type);
    if (env->list->type == TYPE_INSTRUCTION_LIVE)
      printf(" VALID LIVE : %d (PARAM : %s | type %d)\n", env->parsing[12](env), env->list->name, env->list->type);
    if (env->list->type == TYPE_INSTRUCTION_LLD)
      printf(" VALID LLD : %d (PARAM : %s | type %d)\n", env->parsing[24](env), env->list->name, env->list->type);
    if (env->list->type == TYPE_INSTRUCTION_LLDI)
      printf(" VALID LLDI : %d (PARAM : %s | type %d)\n", env->parsing[25](env), env->list->name, env->list->type);
    if (env->list->type == TYPE_INSTRUCTION_LFORK)
      printf(" VALID LFORK : %d (PARAM : %s | type %d)\n", env->parsing[26](env), env->list->name, env->list->type);
    if (env->list->type == TYPE_INSTRUCTION_AFF)
      printf(" VALID AFF : %d (PARAM : %s | type %d)\n", env->parsing[27](env), env->list->name, env->list->type);
    env->list = env->list->next;
  }
  return (1);
}
