/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 11:05:30 by thallot           #+#    #+#             */
/*   Updated: 2019/11/13 15:54:05 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Identifie le charactere comme etant un whitespace
*/

int		is_blank(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
	|| c == '\f' | c == '\0')
		return (1);
	return (0);
}

/*
** Identifie un charactere comme etant un separateur valide (',')
*/

int		is_separator(char c)
{
	if (c == ',')
		return (1);
	return (0);
}

/*
** Fonction de debug, permet d'imprimer une liste (lexeur ou label)
*/

void	print_lst(t_lst *list)
{
	while (list)
	{
		ft_printf("TYPE : %d | [%s]\n", list->type, list->name);
		list = list->next;
	}
}

/*
** Verifie les erreurs suivantes:
** OPT == 0 -> 1 seul param, fichier en param s'ouvre et readable
** OPT != 0 -> on a ajouté au moins un element au lexeur
*/

void	check_error_main(t_env *env, int argc, char **argv, int opt)
{
	if (opt == 0)
	{
		if (argc != 2)
		{
			ft_printf("Erreur : UN parametre (uniquement) requis\n");
			exit(exit_gc(env, 1));
		}
		if ((env->fd_s = open(argv[1], O_RDONLY)) <= 0)
		{
			ft_printf("Erreur : fichier .s n'existe pas\n");
			exit(exit_gc(env, 1));
		}
		if (read(env->fd_s, 0, 0) < 0)
		{
			ft_printf("Erreur : fichier non valide\n");
			exit(exit_gc(env, 1));
		}
	}
	else if (!env->list)
	{
		ft_printf("Erreur : fichier non valide\n");
		exit(exit_gc(env, 1));
	}
}

/*
** FONCTION MAIN
** Appel le parsing du fichier passé en parametre
** Boucle de lecture du fichier .s -> stock chaque element dans une lst lexée
** Appel la boucle de parsing
** Puis les boucles d'ecriture
*/

int		main(int argc, char **argv)
{
	t_env *env;

	if (!(env = (t_env *)ft_memalloc(sizeof(t_env))))
		return (-1);
	check_error_main(env, argc, argv, 0);
	parsing_file_s(env, argv[1]);
	while (get_char(env->fd_s, env->buffer) > 0)
	{
		if (env->buffer[0] == '.')
			get_command(env);
		if (env->buffer[0] == '"')
			get_str(env);
		if (env->buffer[0] == '#')
			get_comment(env);
		if (env->buffer[0] == '\n')
			add_list(&(env->list), "NL", TYPE_NEWLINE, env);
		if (!is_blank(env->buffer[0]))
			get_instruction(env);
	}
	check_error_main(env, argc, argv, 1);
	loop_parser(env);
	w_header(env);
	w_core(env);
	ft_printf("Assemblage dans le fichier ...%s.cor\n", env->file_name);
	return (exit_gc(env, 0));
}

/*
** int my_destructor(void) __attribute__((destructor));
** int my_destructor(void)
** {
**    while (2) ;
**}
*/
