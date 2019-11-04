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

int get_command(int fd, char *buffer, t_lst *lst)
{
  char *command;

  command = ft_strnew(0);
  while (!is_blank(buffer[0]))
  {
    command = strjoinfree(command, buffer, 1);
    get_char(fd, buffer);
  }
  add_list(&lst, command, TYPE_COMMAND);
  ft_strdel(&command);
  return (1);
}

int get_str(int fd, char *buffer, t_lst *lst)
{
  char *comment;

  comment = ft_strnew(0);
	comment = strjoinfree(comment, buffer, 1);
	get_char(fd, buffer);
  while (buffer[0] != '"')
  {
    comment = strjoinfree(comment, buffer, 1);
    get_char(fd, buffer);
  }
	comment = strjoinfree(comment, buffer, 1);
	get_char(fd, buffer);
  add_list(&lst, comment, TYPE_STR);
  ft_strdel(&comment);
  return (1);
}

int get_comment(int fd, char *buffer, t_lst *lst)
{
  char *comment;

  comment = ft_strnew(0);
	comment = strjoinfree(comment, buffer, 1);
	get_char(fd, buffer);
  while (buffer[0] != '\n')
  {
    comment = strjoinfree(comment, buffer, 1);
    get_char(fd, buffer);
  }
  add_list(&lst, comment, TYPE_COMMENT);
  ft_strdel(&comment);
  return (1);
}

int get_instruction(int fd, char *buffer, t_lst *lst)
{
  char *instruction;
	int type;
	char last_char;

	if (buffer[0] == '%')
		type = TYPE_DIRECT;
	else if (ft_isdigit(buffer[0]))
		type = TYPE_INDEX;
	else if (buffer[0] == 'r')
		type = TYPE_REGISTRE;
	else
		type = TYPE_UNKNOWN;
  instruction = ft_strnew(0);
  while (!is_blank(buffer[0]) && !is_separator(buffer[0]))
  {
    instruction = strjoinfree(instruction, buffer, 1);
		last_char = buffer[0];
    get_char(fd, buffer);
  }
	if (last_char == ':')
		add_list(&lst, instruction, TYPE_LABEL);
	else
	{
		if (is_instruction(instruction))
			type = TYPE_INSTRUCTION;
		add_list(&lst, instruction, type);
	}
	if (buffer[0] == ',')
		add_list(&lst, buffer, TYPE_VIRGULE);
	ft_strdel(&instruction);
  return (1);
}
