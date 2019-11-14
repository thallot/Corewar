/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:00:20 by thallot           #+#    #+#             */
/*   Updated: 2019/05/29 12:03:05 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*ft_cjoin(char c, char *str)
{
	char	*s;
	int		i;

	if (!str || !c)
		return (NULL);
	i = 1;
	if (!(s = ft_memalloc(sizeof(char *) * ft_strlen(str) + 1)))
		return (NULL);
	s[0] = c;
	while (str[i - 1] != '\0')
	{
		s[i] = str[i - 1];
		i++;
	}
	s[i] = '\0';
	if (str[0])
		ft_memdel((void**)&str);
	return (s);
}

char	*ft_joinc(char *str, char c)
{
	char	*s;
	int		i;

	if (!str || !c)
		return (NULL);
	if (!(s = ft_memalloc(sizeof(char *) * ft_strlen(str) + 1)))
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		s[i] = str[i];
		i++;
	}
	s[i] = c;
	s[i + 1] = '\0';
	if (str[0])
		ft_memdel((void**)&str);
	return (s);
}
