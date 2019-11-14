/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_asm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 15:49:35 by thallot           #+#    #+#             */
/*   Updated: 2019/11/13 14:36:03 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Retourne le prochain caractere du fichier en lecture
*/

int		get_char(int fd_s, char *buffer)
{
	int ret;

	ret = read(fd_s, buffer, 1);
	buffer[ret] = '\0';
	return (ret);
}

/*
** Lis caractere par caractere la commande,
** jusqu a rencontrer un whitespace.
** Puis l'ajoute dans la liste du lexeur avec le type commande
*/

int		get_command(t_env *env)
{
	char *command;

	command = NULL;
	while (!is_blank(env->buffer[0]))
	{
		command = ft_strjoin_gc(command, env->buffer, env);
		get_char(env->fd_s, env->buffer);
	}
	add_list(&(env->list), command, TYPE_COMMAND, env);
	return (1);
}

/*
** Lis caractere par caractere la string,
** jusqu a rencontrer un \0 ou un guillemet.
** Puis l'ajoute dans la liste du lexeur avec le type STR
*/

int		get_str(t_env *env)
{
	char *str;

	str = NULL;
	str = ft_strjoin_gc(str, env->buffer, env);
	get_char(env->fd_s, env->buffer);
	while (env->buffer[0] != '"' && env->buffer[0] != '\0')
	{
		str = ft_strjoin_gc(str, env->buffer, env);
		get_char(env->fd_s, env->buffer);
	}
	str = ft_strjoin_gc(str, env->buffer, env);
	get_char(env->fd_s, env->buffer);
	add_list(&(env->list), str, TYPE_STR, env);
	return (1);
}

/*
** Lis caractere par caractere le commentaire,
** jusqu a rencontrer un \0 ou un \n.
** Puis l'ajoute dans la liste du lexeur avec le type COMMENT
*/

int		get_comment(t_env *env)
{
	char *comment;

	comment = NULL;
	comment = ft_strjoin_gc(comment, env->buffer, env);
	get_char(env->fd_s, env->buffer);
	while (env->buffer[0] != '\n' && env->buffer[0] != '\0')
	{
		comment = ft_strjoin_gc(comment, env->buffer, env);
		get_char(env->fd_s, env->buffer);
	}
	add_list(&(env->list), comment, TYPE_COMMENT, env);
	return (1);
}

/*
** Determine le type provisoire de l'instruction ou du parametre
** Lis caractere par caractere,
** jusqu a rencontrer un whitespace ou un separateur (,).
** Puis l'ajoute dans la liste du lexeur avec son type
*/

int		get_instruction(t_env *env)
{
	char	*instruction;
	int		type;
	char	last_char;

	last_char = 0;
	instruction = NULL;
	type = get_type_param(env);
	while (!is_blank(env->buffer[0]) && !is_separator(env->buffer[0]))
	{
		instruction = ft_strjoin_gc(instruction, env->buffer, env);
		last_char = env->buffer[0];
		get_char(env->fd_s, env->buffer);
	}
	add_elem(env, type, instruction, last_char);
	return (1);
}
