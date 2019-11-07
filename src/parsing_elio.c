
#include "../include/asm.h"

int is_valid_aff(t_env *env)
{
    env->list = env->list->next;
    if (env->list->type != TYPE_REGISTRE)
    {
        printf("Erreur de type de parametre : devrait etre un registre");
        exit(exit_gc(env, 1));
    }
    is_valid_registre(env);
    return (1);
}

int is_valid_lfork(t_env *env)
{
    env->list = env->list->next;
    if (env->list->type != TYPE_DIRECT)
    {
        printf("Erreur de type de parametre : devrait etre un direct2");
        exit(exit_gc(env, 1));
    }
    return (1);
}

int is_valid_lldi(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE && env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction lldi, parametre 1 : [%s] devrait etre de type RG/ID/D2\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  if (env->list->type == TYPE_REGISTRE)
    is_valid_registre(env);
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction lldi, pas de separateur entre le 1er et le 2eme parametre\n");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
  {
    printf("Erreur de type de parametre pour l'instruction lldi, parametre 2 : [%s] devrait etre de type ID/D2\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_VIRGULE)
  {
    printf("Erreur de formatage pour l'instruction lldi, pas de separateur entre le 2eme et le 3eme parametre\n");
    exit(exit_gc(env, 1));
  }
  env->list = env->list->next;
  if (env->list->type != TYPE_REGISTRE)
  {
    printf("Erreur de type de parametre pour l'instruction lldi, parametre 3 : [%s] devrait etre de type RG\n", env->list->name);
    exit(exit_gc(env, 1));
  }
  is_valid_registre(env);
  return (1);
}

int is_valid_lld(t_env *env)
{
    env->list = env->list->next;
    if (env->list->type != TYPE_INDEX && env->list->type != TYPE_DIRECT && env->list->type != TYPE_LABEL)
    {
        printf("Erreur de type de parametre pour l'instruction lld, parametre 1 : [%s] devrait etre de type ID/D4\n", env->list->name);
        exit(exit_gc(env, 1));
    }
    env->list = env->list->next;
    if (env->list->type != TYPE_VIRGULE)
    {
        printf("Erreur de formatage pour l'instruction lld, pas de separateur entre le 1er et le 2eme parametre\n");
        exit(exit_gc(env, 1));
    }
    env->list = env->list->next;
    if (env->list->type != TYPE_REGISTRE)
    {
        printf("Erreur de type de parametre pour l'instruction lld, parametre 2 : [%s] devrait etre de type RG\n", env->list->name);
        exit(exit_gc(env, 1));
    }
    is_valid_registre(env);
    return (1);
}
