/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:38:27 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/21 18:45:17 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		cb_fork(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	t_listp		*new;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	if (!(new = ft_memalloc(sizeof(t_listp))))
		exit(clean_process(vm->player));
	new->process = *process;
	new->process.active = false;
	new->process.pc = process->param[0].value;
	new->next = vm->player;
	vm->player = new;
}

/*
**fork et lfork prennent un index qui servira de point de depart du prochain prc
*/

t_result		ft_fork(t_env *vm, t_process *process)
{
	int		ad;

	process->pc_instru = process->pc;
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, IND_CODE, false);
	ad = (short)change_endian(process->param[0].ptr, IND_SIZE);
	ad = get_adress(process->pc_instru, ad, false);
	process->param[0].value = ad;
	process->active = true;
	process->delay = 800 - 1;
	return (cb_fork);
}

t_result		ft_lfork(t_env *vm, t_process *process)
{
	int		ad;

	process->pc_instru = process->pc;
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, IND_CODE, false);
	ad = (short)change_endian(process->param[0].ptr, IND_SIZE);
	ad = get_adress(process->pc_instru, ad, true);
	process->param[0].value = ad;
	process->active = true;
	process->delay = 1000 - 1;
	return (cb_fork);
}
