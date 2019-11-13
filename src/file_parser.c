/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 12:38:38 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/08 12:38:41 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/asm.h"

char	*ft_strndup_gc(t_env *env, const char *s1, size_t n)
{
	size_t	i;
	char	*dest;

	if (!(dest = (char *)malloc(sizeof(*dest) * n + 1)))
		exit(exit_gc(env, -1));
	i = 0;
	while (s1[i] != '\0' && i < n)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
    add_list_gc(env, dest);
	return (dest);
}

int     parsing_file_s(t_env *env, char *file_path)
{
    char    *dot_s;
    int     len;

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
        printf("valid .s file needed\n");
        exit(exit_gc(env, 1));
    }
    return (0);
}
