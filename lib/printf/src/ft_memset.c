/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/02 09:41:32 by thallot           #+#    #+#             */
/*   Updated: 2019/04/08 13:26:47 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *str_cpy;

	str_cpy = b;
	while (len)
	{
		*str_cpy = c;
		str_cpy++;
		len--;
	}
	return (b);
}
