/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:38:27 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/19 16:41:12 by jjaegle          ###   ########.fr       */
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

t_result		ft_fork(t_env *vm, t_process *process)
{
	int		ad;
	int		start;

	start = process->pc;
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, IND_CODE, false);
	ad = (short)change_endian(process->param[0].ptr, IND_SIZE);
	ft_printf("FORK : ad = %d\n", ad);
	ad = get_adress(start, ad, false);
	ft_printf("FORK : ad = %d\n", ad);
	process->param[0].value = ad;
	process->active = true;
	process->delay = 800 - 1;
	return (cb_fork);
}

t_result		ft_lfork(t_env *vm, t_process *process)
{
	int		ad;
	int		start;

	start = process->pc;
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, IND_CODE, false);
	ad = (short)change_endian(process->param[0].ptr, IND_SIZE);
	ft_printf("FORK : ad = %d\n", ad);
	ad = get_adress(start, ad, true);
	ft_printf("FORK : ad = %d\n", ad);
	process->param[0].value = ad;
	process->active = true;
	process->delay = 800 - 1;
	return (cb_fork);
}
