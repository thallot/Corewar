/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 14:49:49 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/01 14:36:49 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = ft_strlen(str) - 1;
	j = 0;
	while (j < i)
	{
		tmp = str[i];
		str[i--] = str[j];
		str[j++] = tmp;
	}
	return (str);
}
