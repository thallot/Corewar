/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:19:53 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/19 16:24:44 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_size(int type, enum e_bool d2)
{
	if (type == UNDEF)
		return (0);
	if (type == IND_CODE || (type == DIR_CODE && d2 == true))
		return (IND_SIZE);
	else if (type == DIR_CODE)
		return (DIR_SIZE);
	else
		return (T_REG);
}
