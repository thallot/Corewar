/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 12:01:19 by thallot           #+#    #+#             */
/*   Updated: 2019/04/08 13:33:58 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	int i;

	i = 0;
	if (!s1 && !s2)
		return (1);
	else if (!s1 || !s2)
		return (0);
	else
	{
		if (ft_strncmp(s1, s2, n) == 0)
			return (1);
		else
			return (0);
	}
}
