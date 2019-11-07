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
  if (env->list->type != TYPE_DIRECT)
  {
    printf("Erreur de type de parametre pour l'instruction live, parametre 1 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  return (1);
}

int is_valid_ld(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
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
    printf("Erreur de formatage pour l'instruction st, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction st, parametre 2 : [%s]\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_add(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction add, parametre 1 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction add, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction add, parametre 2 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction add, pas de separateur dans le 2e et le 3e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction add, parametre 3 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_sub(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction sub, parametre 1 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction sub, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction sub, parametre 2 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction sub, pas de separateur dans le 2e et le 3e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction sub, parametre 3 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_and(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction and, parametre 1 : [%s] devrait etre de type registre / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction and, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction and, parametre 2 : [%s] devrait etre de type registre / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction and, pas de separateur dans le 2e et le 3e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction and, parametre 3 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_or(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction or, parametre 1 : [%s] devrait etre de type registre / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction or, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction or, parametre 2 : [%s] devrait etre de type registre / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction or, pas de separateur dans le 2e et le 3e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction or, parametre 3 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_xor(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction xor, parametre 1 : [%s] devrait etre de type registre / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction xor, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction xor, parametre 2 : [%s] devrait etre de type registre / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction xor, pas de separateur dans le 2e et le 3e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction xor, parametre 3 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_zjmp(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT_2 && env->list->type != TYPE_DIRECT)
  {
    printf("Erreur de type de parametre pour l'instruction zjmp, parametre 1 : [%s] devrait etre de type directe 2 ou directe 4\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  return (1);
}

int is_valid_ldi(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction ldi, parametre 1 : [%s] devrait etre de type registre / DIRECTE 2 / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction ldi, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT && env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction ldi, parametre 2 : [%s] devrait etre de type  DIRECTE 2 / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction ldi, pas de separateur dans le 2e et le 3e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction ldi, parametre 3 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_sti(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction sti, parametre 1 : [%s] devrait etre de type registre\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (!is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction sti, pas de separateur dans le 1er et le 2e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_DIRECT && env->list->type != TYPE_INDEX && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction sti, parametre 2 : [%s] devrait etre de type  DIRECTE 2 / DIRECTE 4 / INDIRECT\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction sti, pas de separateur dans le 2e et le 3e parametre");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_REGISTRE && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction sti, parametre 3 : [%s] devrait etre de type DIRECTE 2 / DIRECTE 4 / INDIRECTE \n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE && !is_valid_registre(env))
    exit(exit_gc(env, 1));
  return (1);
}

int is_valid_fork(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT)
  {
    printf("Erreur de type de parametre pour l'instruction fork, parametre 1 : [%s] devrait etre de type directe 2 ou directe 4\n", env->list->name);
    exit(exit_gc(env, 1));
  }
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
  env->parsing[15] = is_valid_add;
  env->parsing[16] = is_valid_sub;
  env->parsing[17] = is_valid_and;
  env->parsing[18] = is_valid_or;
  env->parsing[19] = is_valid_xor;
  env->parsing[20] = is_valid_zjmp;
  env->parsing[21] = is_valid_ldi;
  env->parsing[22] = is_valid_sti;
  env->parsing[23] = is_valid_fork;
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
    if (env->list->type != TYPE_COMMENT)
      env->parsing[env->list->type](env);
    env->list = env->list->next;
  }
  return (1);
}
