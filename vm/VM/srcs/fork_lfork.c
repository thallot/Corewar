/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_lfork.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:38:27 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/14 17:47:31 by jjaegle          ###   ########.fr       */
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
	new->process.active = false;
	new->process = *process;
	new->process.pc = process->param[0].value;
	// ft_printf("CBF : pc = %d\n", new->process.pc);
	new->next = vm->player;
	// ft_printf("oldfirstpc = %d\n", new->next->process.pc);
	vm->player = new;
	// ft_printf("CBF : vm->player = %d\n", vm->player->process.pc);
}

t_result		ft_fork(t_env *vm, t_process *process)
{
	int		ad;
	int		start;

	start = process->pc;
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, IND_SIZE);
	process->param[0].size = IND_SIZE;
	ad = (short)change_endian(process->param[0].ptr, IND_SIZE);
	// ft_printf("FORK : ad = %d\n", ad);
	ad = get_adress(start, ad, false);
	// ft_printf("FORK : ad = %d\n", ad);
	process->param[0].value = ad;
	process->active = true;
	process->delay = 800 - 1;
	return (cb_fork);
}
