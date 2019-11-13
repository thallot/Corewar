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

int get_size(t_env *env)
{
  if (env->list->type == TYPE_REGISTRE || (env->list->type >= TYPE_INSTRUCTION_LIVE && env->list->type <= TYPE_INSTRUCTION_AFF))
    return (1);
  if (env->list->type == TYPE_DIRECT_2 || env->list->type == TYPE_INDEX || env->list->type == TYPE_LABEL_DEFINITION || env->list->type == TYPE_LABEL)
    return (2);
  if (env->list->type == TYPE_DIRECT_4)
    return (4);
  printf("Mauvais type de parametre dans get_size sur %s (type : %d)", env->list->name, env->list->type);
  exit(exit_gc(env, 1));
}

void print_error(t_env *env, char *instr, int nb)
{
  printf("Erreur de type de parametre pour l'instruction %s, parametre %d : [%s]\n", instr, nb, env->list->name);
  exit(exit_gc(env, 1));
}

int is_valid_separator(t_env *env, char *instr, int one, int two)
{
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction %s, pas de separateur dans le %de et le %de parametre", instr, one, two);
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  return (1);
}

int is_valid_param(t_env *env)
{
  if (((env->list->type == TYPE_DIRECT && env->list->name[1] == ':') || env->list->type == TYPE_LABEL))
    is_valid_label_call(env);
  if (env->list->type == TYPE_REGISTRE)
    is_valid_registre(env);
  return (1);
}

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
  {
    env->list->name = ft_memmove(env->list->name, env->list->name + 1, size);
    env->list->name[size]= '\0';
    env->list->name[size - 1]= '\0';
    return (1);
  }
  printf("Chaine de caractere mal formatée [%s]\n", env->list->name);
  exit(exit_gc(env, 1));
}

int is_valid_label_definition(t_env *env)
{
  int i;
  int size;
  char c;
  // t_lst *head;
  t_lst *current;

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
        break ;
      printf("Erreur de formatage du label [%s], caractere invalide : %c\n", env->list->name, c);
      exit(exit_gc(env, 1));
    }
  }
  current = env->label;
  while (current)
  {
    if (!ft_strcmp(current->name, env->list->name))
    {
      current->type = env->size;
      return (1);
    }
    current = current->next;
  }
  return (1);
}

int is_valid_label_call(t_env *env)
{
  int i;
  t_lst *head;

  i = 0;
  if (env->list->name[i] == '%')
    i++;
  if (env->list->name[i] == ':')
    i++;
  head = env->label;
  while (env->label)
  {
    if (!ft_strcmp(env->label->name, i + env->list->name))
    {
      env->label = head;
      return (1);
    }
    env->label = env->label->next;
  }
  printf("Le label %s n'existe pas\n", i + env->list->name);
  exit(exit_gc(env, 1));
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
  env->size += T_INSTRUCTION;
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT)
  {
    printf("Erreur de type de parametre pour l'instruction live, parametre 1 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  is_valid_param(env);
  env->list->type = TYPE_DIRECT_4;
  env->size += get_size(env);
  return (1);
}

int is_valid_ld(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "ld", 1);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "ld", 1, 2);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "ld", 2);
  is_valid_param(env);
  env->size += get_size(env);
  return (1);
}

int is_valid_st(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "st", 1);
  env->size += get_size(env);
  is_valid_param(env);
  env->list = env->list->next;
  is_valid_separator(env, "st", 1, 2);
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "st", 2);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_add(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "add", 1);
  env->size += get_size(env);
  is_valid_param(env);
  env->list = env->list->next;
  is_valid_separator(env, "add", 1, 2);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "add", 2);
  env->size += get_size(env);
  is_valid_param(env);
  env->list = env->list->next;
  is_valid_separator(env, "add", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "add", 3);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_sub(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "sub", 1);
  env->size += get_size(env);
  is_valid_param(env);
  env->list = env->list->next;
  is_valid_separator(env, "sub", 1, 2);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "sub", 2);
  env->size += get_size(env);
  is_valid_param(env);
  env->list = env->list->next;
  is_valid_separator(env, "sub", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "sub", 3);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_and(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "and", 1);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
  env->size += get_size(env);
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  is_valid_separator(env, "and", 1, 2);
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "and", 2);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
  env->size += get_size(env);
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  is_valid_separator(env, "and", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "and", 3);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_or(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "or", 1);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
  env->size += get_size(env);
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  is_valid_separator(env, "or", 1, 2);
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "or", 2);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "or", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "or", 3);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_xor(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "xor", 1);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "xor", 1, 2);
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "xor", 2);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "xor", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "xor", 3);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_zjmp(t_env *env)
{
  env->size += T_INSTRUCTION;
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT)
    print_error(env, "zjmp", 1);
  is_valid_param(env);
  env->list->type = TYPE_DIRECT_2;
  env->size += get_size(env);
  return (1);
}

int is_valid_ldi(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "ldi", 1);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "ldi", 1, 2);
  if (env->list->type != TYPE_DIRECT && env->list->type != TYPE_REGISTRE)
    print_error(env, "ldi", 2);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "ldi", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "ldi", 3);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_sti(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "sti", 1);
  env->size += get_size(env);
  is_valid_param(env);
  env->list = env->list->next;
  is_valid_separator(env, "sti", 1, 2);
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
    print_error(env, "sti", 2);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "sti", 2, 3);
  if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_REGISTRE && env->list->type != TYPE_LABEL)
    print_error(env, "sti", 3);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  return (1);
}

int is_valid_fork(t_env *env)
{
  env->size += T_INSTRUCTION;
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT)
    print_error(env, "fork", 1);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  return (1);
}

void  init_parsing_tab(t_env *env)
{
  env->parsing[TYPE_COMMAND] = is_valid_command;
  env->parsing[TYPE_STR] = is_valid_str;
  env->parsing[TYPE_LABEL_DEFINITION] = is_valid_label_definition;
  env->parsing[TYPE_REGISTRE] = is_valid_registre;
  env->parsing[TYPE_INSTRUCTION_LIVE] = is_valid_live;
  env->parsing[TYPE_INSTRUCTION_LD] = is_valid_ld;
  env->parsing[TYPE_INSTRUCTION_ST] = is_valid_st;
  env->parsing[TYPE_INSTRUCTION_ADD] = is_valid_add;
  env->parsing[TYPE_INSTRUCTION_SUB] = is_valid_sub;
  env->parsing[TYPE_INSTRUCTION_AND] = is_valid_and;
  env->parsing[TYPE_INSTRUCTION_OR] = is_valid_or;
  env->parsing[TYPE_INSTRUCTION_XOR] = is_valid_xor;
  env->parsing[TYPE_INSTRUCTION_ZJMP] = is_valid_zjmp;
  env->parsing[TYPE_INSTRUCTION_LDI] = is_valid_ldi;
  env->parsing[TYPE_INSTRUCTION_STI] = is_valid_sti;
  env->parsing[TYPE_INSTRUCTION_FORK] = is_valid_fork;
  env->parsing[TYPE_INSTRUCTION_LLD] = is_valid_lld;
  env->parsing[TYPE_INSTRUCTION_LLDI] = is_valid_lldi;
  env->parsing[TYPE_INSTRUCTION_LFORK] = is_valid_lfork;
  env->parsing[TYPE_INSTRUCTION_AFF] = is_valid_aff;
}

int loop_parser(t_env *env)
{
  t_lst *head;

  head = env->list;
  init_parsing_tab(env);
  while (env->list)
  {
    if (env->list->type >= TYPE_INSTRUCTION_LIVE && env->list->type <= TYPE_LABEL_DEFINITION)
      env->parsing[env->list->type](env);
    else if (env->list->type != TYPE_COMMENT)
    {
      printf("Element inconnu : %s\n", env->list->name);
      exit(exit_gc(env, 1));
    }
    env->list = env->list->next;
  }
  env->list = head;
  return (1);
}
