/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:46:00 by thallot           #+#    #+#             */
/*   Updated: 2019/07/31 12:34:18 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_isword(char before, char current, char c)
{
	return ((before == c || !before) && current != c);
}

static int	ft_count(char const *s, char c)
{
	int i;
	int nb_word;

	i = 0;
	nb_word = 0;
	while (s[i])
	{
		if (ft_isword(s[i - 1], s[i], c))
			nb_word++;
		i++;
	}
	return (nb_word);
}

static int	ft_strlen_split(const char *s, char c)
{
	unsigned int i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	char	*tmp;
	int		i;
	int		j;

	tmp = (char*)s;
	i = 0;
	j = 0;
	if (!s || !(tab = (char**)malloc((ft_count(s, c) + 2) * sizeof(char*))))
		return (NULL);
	while (tmp[i])
	{
		if (ft_isword(tmp[i - 1], tmp[i], c) || i == 0)
		{
			if (!(tab[j] = ft_strndup(&tmp[i], ft_strlen_split(&tmp[i], c))))
				return (NULL);
			j++;
		}
		i++;
	}
	tab[j] = 0;
	return (tab);
}
