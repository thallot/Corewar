/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/10 13:22:01 by edillenb          #+#    #+#             */
/*   Updated: 2019/10/16 12:18:13 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strsub(const char **s, unsigned int strt, size_t ln, int o)
{
	char	*new;
	size_t	i;

	i = 0;
	if (!s || !(new = ft_strnew(ln)))
		return (NULL);
	while (ln--)
		new[i++] = (*s)[strt++];
	if (o == 1)
		ft_memdel((void**)s);
	return (new);
}
