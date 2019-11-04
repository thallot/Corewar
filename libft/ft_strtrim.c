/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 09:47:49 by thallot           #+#    #+#             */
/*   Updated: 2019/04/08 14:57:31 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_space_before(char const *s)
{
	size_t i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i++;
	return (i);
}

static size_t	ft_space_after(char const *s)
{
	size_t len;
	size_t i;

	i = ft_strlen(s) - 1;
	len = i;
	while (s[i] == ' ' || s[i] == '\t' || s[i] == '\n')
		i--;
	return (len - i);
}

static	int		ft_full_blank(char const *s)
{
	size_t i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

char			*ft_strtrim(char const *s)
{
	char	*str;
	size_t	len_start;
	size_t	len_end;
	size_t	len;

	str = NULL;
	if (s)
	{
		if (ft_full_blank(s))
		{
			str = ft_strnew(0);
			return (str);
		}
		len = ft_strlen(s);
		len_start = ft_space_before(s);
		len_end = len - len_start - ft_space_after(s);
		str = ft_strnew(len_end - len_start);
		if (str == NULL)
			return (NULL);
		str = ft_strsub(s, len_start, len_end);
	}
	return (str);
}
