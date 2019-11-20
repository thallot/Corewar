/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 16:19:53 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/20 14:40:43 by jjaegle          ###   ########.fr       */
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

/*
** remplace les valeurs initiales des parametres par leur valeur effective
** en se basant sur leur type
*/

void            set_param_value(unsigned char *mem, t_process *process, int i
		, enum e_bool lg)
{
    unsigned char   *idx;

    if (process->param[i - 1].type == IND_CODE)
    {
        idx = &mem[get_adress(process->pc_instru
				, (short)process->param[i - 1].value, lg)];
        process->param[i - 1].value = change_endian(idx, REG_SIZE);
    }
    else if (process->param[i - 1].type == REG_CODE)
        process->param[i - 1].value = 
			*(int*)process->records[(short)process->param[i - 1].value - 1];
}

