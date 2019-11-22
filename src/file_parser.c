/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:38:38 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/13 15:29:47 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

/*
** Parse le nom du ouvert par l'assembler
** Si le fichier n'est pas un .s valide la fonction exit
** Sinon le nom est stocké dans env->file_name
*/

int		parsing_file_s(t_env *env, char *file_path)
{
	char	*dot_s;
	int		len;

	dot_s = ft_strrchr(file_path, '/');
	if (!(dot_s = ft_strrchr(file_path, '/')))
		dot_s = file_path;
	else
		dot_s = dot_s + 1;
	len = ft_strlen(dot_s);
	if (len > 2 && dot_s[len - 1] == 's' && dot_s[len - 2] == '.')
		env->file_name = ft_strndup_gc(env, dot_s, len - 2);
	else
	{
		ft_printf("Erreur : valid .s file needed\n");
		exit(exit_gc(env, 1));
	}
	return (0);
}
