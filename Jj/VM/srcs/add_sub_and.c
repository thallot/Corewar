/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:32:27 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/13 16:50:55 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			cb_st(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	void		*src;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	src = process->records[process->param[0].value - 1];
	ft_memrev(src, REG_SIZE);
	ft_memcpy(process->param[1].ptr, src, REG_SIZE);
	ft_printf("CBST : valeur storer = %d\n", change_endian(src, REG_SIZE));
}
