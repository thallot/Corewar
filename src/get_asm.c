/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_asm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:49:35 by thallot           #+#    #+#             */
/*   Updated: 2019/11/04 15:49:36 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

int get_char(int fd, char *buffer)
{
  int ret;

  ret = read(fd, buffer, 1);
  buffer[ret] = '\0';
  return (ret);
}

int get_command(t_env *env)
{
  char *command;

  command = NULL;
  while (!is_blank(env->buffer[0]))
  {
    command = ft_strjoin_gc(command, env->buffer, env);
    get_char(env->fd, env->buffer);
  }
  add_list(&(env->list), command, TYPE_COMMAND, env);
  return (1);
}

int get_str(t_env *env)
{
  char *str;

  str = NULL;
	str = ft_strjoin_gc(str, env->buffer, env);
	get_char(env->fd, env->buffer);
  while (env->buffer[0] != '"' && env->buffer[0] != '\n')
  {
    str = ft_strjoin_gc(str, env->buffer, env);
    get_char(env->fd, env->buffer);
  }
	str = ft_strjoin_gc(str, env->buffer, env);
	get_char(env->fd, env->buffer);
  add_list(&(env->list), str, TYPE_STR, env);
  return (1);
}

int get_comment(t_env *env)
{
  char *comment;

  comment = NULL;
	comment = ft_strjoin_gc(comment, env->buffer, env);
	get_char(env->fd, env->buffer);
  while (env->buffer[0] != '\n')
  {
    comment = ft_strjoin_gc(comment, env->buffer, env);
    get_char(env->fd, env->buffer);
  }
  add_list(&(env->list), comment, TYPE_COMMENT, env);
  return (1);
}

int get_instruction(t_env *env)
{
  char *instruction;
	int type;
  int instruction_type;
	char last_char;

  last_char = 0;
	if (env->buffer[0] == '%')
		type = TYPE_DIRECT;
	else if (ft_isdigit(env->buffer[0]))
		type = TYPE_INDEX;
	else if (env->buffer[0] == 'r')
		type = TYPE_REGISTRE;
  else if (env->buffer[0] == ':')
  	type = TYPE_LABEL;
	else
		type = TYPE_UNKNOWN;
  instruction = NULL;
  while (!is_blank(env->buffer[0]) && !is_separator(env->buffer[0]))
  {
    instruction = ft_strjoin_gc(instruction, env->buffer, env);
		last_char = env->buffer[0];
    get_char(env->fd, env->buffer);
  }
	if (last_char == ':')
    add_list(&(env->list), instruction, TYPE_LABEL_DEFINITION, env);
	else if (instruction)
	{
    if (type == TYPE_DIRECT)
    {
      if (ft_isnumber(&instruction[1], 0))
        type = TYPE_DIRECT_4;
      else
        type = TYPE_DIRECT_2;
    }
		if ((instruction_type = is_instruction(instruction)))
			type = instruction_type;
    else if (ft_isnumber(instruction, 1))
      type = TYPE_INDEX;
		add_list(&(env->list), instruction, type, env);
	}
	if (env->buffer[0] == ',')
    add_list(&(env->list), ",", TYPE_VIRGULE, env);
  return (1);
}
