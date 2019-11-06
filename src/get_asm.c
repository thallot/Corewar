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

  command = ft_strnew(0);
  while (!is_blank(env->buffer[0]))
  {
    //integrer GC dans strjoinfree ?
    command = strjoinfree(command, env->buffer, 1);
    get_char(env->fd, env->buffer);
  }
  if (!(add_list(&(env->list), command, TYPE_COMMAND, env)))
  {
    ft_strdel(&command);
    return (0);
  }
  ft_strdel(&command);
  return (1);
}

int get_str(t_env *env)
{
  char *str;

  str = ft_strnew(0);
	str = strjoinfree(str, env->buffer, 1);
	get_char(env->fd, env->buffer);
  while (env->buffer[0] != '"')
  {
    str = strjoinfree(str, env->buffer, 1);
    get_char(env->fd, env->buffer);
  }
	str = strjoinfree(str, env->buffer, 1);
	get_char(env->fd, env->buffer);
  if (!(add_list(&(env->list), str, TYPE_STR, env)))
  {
    ft_strdel(&str);
    return (0);
  }
  ft_strdel(&str);
  return (1);
}

int get_comment(t_env *env)
{
  char *comment;

  comment = ft_strnew(0);
	comment = strjoinfree(comment, env->buffer, 1);
	get_char(env->fd, env->buffer);
  while (env->buffer[0] != '\n')
  {
    comment = strjoinfree(comment, env->buffer, 1);
    get_char(env->fd, env->buffer);
  }
  if (!(add_list(&(env->list), comment, TYPE_COMMENT, env)))
  {
    ft_strdel(&comment);
    return (0);
  }
  ft_strdel(&comment);
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
  instruction = ft_strnew(0);
  while (!is_blank(env->buffer[0]) && !is_separator(env->buffer[0]))
  {
    instruction = strjoinfree(instruction, env->buffer, 1);
		last_char = env->buffer[0];
    get_char(env->fd, env->buffer);
  }
	if (last_char == ':')
  {
    if (!(add_list(&(env->list), instruction, TYPE_LABEL_DEFINITION, env)))
    {
      ft_strdel(&instruction);
      return(0);
    }
  }
	else
	{
		if ((instruction_type = is_instruction(instruction)))
			type = instruction_type;
    else if (ft_isnumber(instruction))
      type = TYPE_INDEX;
		if (!(add_list(&(env->list), instruction, type, env)))
    {
      ft_strdel(&instruction);
      return (0);
    }
	}
	if (env->buffer[0] == ',')
	{
    if (!(add_list(&(env->list), env->buffer, TYPE_VIRGULE, env)))
    {
      ft_strdel(&instruction);
      return (0);
    }
  }
	ft_strdel(&instruction);
  return (1);
}
