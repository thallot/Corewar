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

int is_valid_live(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT)
    return (0);
  env->list = env->list->next;
  return (1);
}

int is_valid_live(t_env *env)
{
  env->list = env->list->next;
  if (env->list->type != TYPE_DIRECT)
    return (0);
  env->list = env->list->next;
  return (1);
}
