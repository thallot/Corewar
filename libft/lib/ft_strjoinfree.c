/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/13 19:35:34 by jjaegle           #+#    #+#             */
/*   Updated: 2019/05/23 08:22:43 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strjoinfree(char *s1, char *s2, int i)
{
	char	*dest;

	if (!(s1 || s2))
		return (NULL);
	if (!(dest = ft_strjoin(s1, s2)))
		return (NULL);
	if (i == 1 || i == 3)
		s1 = my_free(s1);
	if (i == 2 || i == 3)
		s2 = my_free(s2);
	return (dest);
}
