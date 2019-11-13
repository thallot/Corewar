
#include "../include/asm.h"

int is_valid_aff(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "aff", 1);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_lfork(t_env *env)
{
  env->size += T_INSTRUCTION;
    env->list = env->list->next;
    if (env->list->type != TYPE_DIRECT)
      print_error(env, "lfork", 1);
    is_valid_param(env);
    env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
    env->size += get_size(env);
    return (1);
}

int is_valid_lldi(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
    print_error(env, "lldi", 1);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "lldi", 1, 2);
  if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
    print_error(env, "lldi", 2);
  is_valid_param(env);
  env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_2 : env->list->type;
  env->size += get_size(env);
  env->list = env->list->next;
  is_valid_separator(env, "lldi", 2, 3);
  if (env->list->type != TYPE_REGISTRE)
    print_error(env, "lldi", 3);
  env->size += get_size(env);
  is_valid_param(env);
  return (1);
}

int is_valid_lld(t_env *env)
{
  env->size += T_INSTRUCTION + T_OCP;
    env->list = env->list->next;
    if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
      print_error(env, "lld", 1);
    is_valid_param(env);
    env->list->type = env->list->type == TYPE_DIRECT ? TYPE_DIRECT_4 : env->list->type;
    env->size += get_size(env);
    env->list = env->list->next;
    is_valid_separator(env, "lld", 1, 2);
    if (env->list->type != TYPE_REGISTRE)
      print_error(env, "lld", 2);
    env->size += get_size(env);
    is_valid_param(env);
    return (1);
}
