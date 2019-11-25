/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 10:48:42 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/02 09:23:38 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <string.h>

void	*ft_memalloc(size_t size)
{
	char	*str;
	size_t	i;

	if ((str = malloc(sizeof(char) * size)) == NULL)
		return (NULL);
	i = 0;
	while (i < size)
		str[i++] = 0;
	return (str);
}
