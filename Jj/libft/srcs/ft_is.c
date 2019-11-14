/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 20:04:02 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/07 12:51:45 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		is_nombre(char type)
{
	if (type == 'c' || type == 's')
		return (0);
	return (1);
}

int		is_base(char type)
{
	if (type == 'x' || type == 'X' || type == 'o')
		return (1);
	return (0);
}
