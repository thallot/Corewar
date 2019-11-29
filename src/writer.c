/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 15:43:51 by thallot           #+#    #+#             */
/*   Updated: 2019/11/25 16:15:18 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Parse les premiers elements de notre liste issue du lexeur et verifie que
** les informations liées au header son correctes
*/

void	check_error(t_env *env, char *name)
{
	char *str;

	str = env->list->name;
	zap_all(env, 0);
	if (ft_strcmp(env->list->name, NAME_CMD_STRING))
	{
		ft_printf("Erreur : Le nom du champion doit être la 1ère commande(%s)\n"
		, str);
		exit(exit_gc(env, 1));
	}
	zap_all(env, 0);
	env->list = env->list->next;
	ft_strcpy(name, env->list->name);
	env->list = env->list->next;
	zap_all(env, 0);
	if (ft_strcmp(env->list->name, COMMENT_CMD_STRING))
	{
		ft_printf("Erreur : Le commentaire doit être la 2ème commande (%s)\n"
		, str);
		exit(exit_gc(env, 1));
	}
	zap_all(env, 0);
	env->list = env->list->next;
}

/*
** Crée le fichier .cor et ecrit les éléments correspondant au header
** dans le fichier créé
*/

void	w_header(t_env *env)
{
	int		magic;
	char	name[132];
	char	comment[2052];
	int		size;

	size = env->size;
	magic = 15369203;
	ft_bzero(name, 132);
	ft_bzero(comment, 2052);
	check_error(env, name);
	ft_strcpy(comment, env->list->name);
	ft_memrev(&magic, 4);
	ft_memrev(&size, 4);
	env->fd_cor = open(ft_strjoin_gc(env->file_name, ".cor", env),
	O_TRUNC | O_RDWR | O_CREAT, 0777);
	write(env->fd_cor, &magic, 4);
	write(env->fd_cor, name, 132);
	write(env->fd_cor, &size, 4);
	write(env->fd_cor, comment, 2052);
	env->list = env->list->next;
}

/*
** Ecrit en memoire dans le fichier .cor l'instruction rencontrée
** et si nécessaire écrit également à la suite son OCP (byte d'encodage)
*/

void	write_instr(t_env *env, int *cpt_instr, int *cpt_octet, int octet)
{
	int ocp;

	*cpt_instr = *cpt_octet;
	octet = get_size(env);
	write(env->fd_cor, &(env->list)->type, 1);
	if (env->list->type != TYPE_ZJMP
	&& env->list->type != TYPE_LIVE
	&& env->list->type != TYPE_FORK
	&& env->list->type != TYPE_LFORK)
	{
		*cpt_octet = (*cpt_octet) + 1;
		ocp = generate_ocp(env);
		write(env->fd_cor, &ocp, octet);
	}
}

/*
** Ecrit en memoire dans le fichier .s un element de type parametre
** sont fournis en arg: le cpt_instr (idx de l'instru dont depend le param)
** ainsi que la taille en memoire en octet du param
*/

void	write_param(t_env *env, int *cpt_instr, int octet)
{
	int label_index;
	int op;

	if (env->list->type == TYPE_DIRECT_2 || env->list->type == TYPE_DIRECT_4)
	{
		if (env->list->name[1] == ':')
		{
			label_index = looking_for_label(env, env->list->name + 2);
			op = label_index - (*cpt_instr) + 1;
		}
		else
			op = ft_atoi(&(env->list)->name[1]);
	}
	else if (env->list->type == TYPE_LABEL)
	{
		label_index = looking_for_label(env, env->list->name + 1);
		op = label_index - (*cpt_instr) + 1;
	}
	else if (env->list->type == TYPE_INDEX)
		op = ft_atoi(env->list->name);
	else if (env->list->type == TYPE_REGISTRE)
		op = ft_atoi(&(env->list)->name[1]);
	ft_memrev(&op, octet);
	write(env->fd_cor, &op, octet);
}

/*
** Boucle principale d'ecriture dans le fichier .cor
** On itere notre liste issue du lexeur et on ecrit a l'aide des fonctions
** ci-dessus les elements un à un dans le fichier .cor
*/

void	w_core(t_env *env)
{
	int cpt_octet;
	int cpt_instr;
	int octet;

	cpt_octet = 0;
	while (env->list)
	{
		zap_all(env, 1);
		if (!env->list)
			break ;
		octet = get_size(env);
		cpt_octet += octet;
		if (env->list->type >= 1 && env->list->type <= 16)
			write_instr(env, &cpt_instr, &cpt_octet, octet);
		else
			write_param(env, &cpt_instr, octet);
		env->list = env->list->next;
	}
}
