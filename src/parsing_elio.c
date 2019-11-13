
#include "../include/asm.h"

int is_valid_aff(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
      printf("Erreur de type de parametre : devrait etre un registre");
      exit(exit_gc(env, 1));
  }
  env->size += get_size(env);
  is_valid_registre(env);
  return (1);
}

int is_valid_lfork(t_env *env)
{
  env->size += T_INSTRUCTION;
    env->list = env->list->next;
    if (env->list->type != TYPE_DIRECT)
    {
        printf("Erreur de type de parametre : devrait etre un direct2");
        exit(exit_gc(env, 1));
    }
    if (env->list->type == TYPE_DIRECT && env->list->name[1] == ':')
      is_valid_label_call(env);
    env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
    env->size += get_size(env);
    return (1);
}

int is_valid_lldi(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction lldi, parametre 1 : [%s] devrait etre de type RG/ID/D2\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (((env->list->type == TYPE_DIRECT && env->list->name[1] == ':') || env->list->type == TYPE_LABEL))
    is_valid_label_call(env);
  if (env->list->type == TYPE_REGISTRE)
    is_valid_registre(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "lldi", 1, 2);
  if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction lldi, parametre 2 : [%s] devrait etre de type ID/D2\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (((env->list->type == TYPE_DIRECT && env->list->name[1] == ':') || env->list->type == TYPE_LABEL))
    is_valid_label_call(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "lldi", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction lldi, parametre 3 : [%s] devrait etre de type RG\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  env->size += get_size(env);
  is_valid_registre(env);
  return (1);
}

int is_valid_lld(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
    env->list = env->list->next;
    if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
    {
        printf("Erreur de type de parametre pour l'instruction lld, parametre 1 : [%s] devrait etre de type ID/D4\n", env->list->name);
        exit(exit_gc(env, 1));
    }
    if (((env->list->type == TYPE_DIRECT && env->list->name[1] == ':') || env->list->type == TYPE_LABEL))
      is_valid_label_call(env);
    env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
    env->size += get_size(env);
    env->list = env->list->next;
    is_valid_separator(env, "lld", 1, 2);
    if (env->list->type != TYPE_REGISTRE)
    {
        printf("Erreur de type de parametre pour l'instruction lld, parametre 2 : [%s] devrait etre de type RG\n", env->list->name);
        exit(exit_gc(env, 1));
    }
    env->size += get_size(env);
    is_valid_registre(env);
    return (1);
}
