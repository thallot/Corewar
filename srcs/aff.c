/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:10:06 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/28 11:48:18 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		cb_aff(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	if (!vm->visu)
		ft_printf("%c\n", *(int*)process->records[process->param[0].value - 1]);
}

t_result		ft_aff(t_env *vm, t_process *process)
{
	int		rec;

	process->pc_instru = process->pc;
	process->pc += 2;
	rec = vm->memory[process->pc];
	if (rec < 1 || rec > 16)
		return (NULL);
	process->param[0].value = rec;
	process->active = true;
	process->delay = 2 - 1;
	process->pc++;
	return (cb_aff);
}
