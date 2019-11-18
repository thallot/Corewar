/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:58:08 by thallot           #+#    #+#             */
/*   Updated: 2019/11/18 13:58:09 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			cb_fork(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	int i;

  i = 0;
	vm = (t_env*)pvm;
	process = (t_process*)pproc;
  if (create_process(vm))
		write(2, "Malloc error\n", 13);
  vm->player->process.pc = process->param[0].value;
  vm->player->process.carry  = process->carry;
  while (i++ <= 15)
    ft_memcpy(vm->player->process.records[i], process->records[i], 4);
  printf("Creation d'un processeur en %d\n", vm->player->process.pc);
}

t_result		ft_fork(t_env *vm, t_process *process)
{
  printf("ENTER FORK\n");
  process->pc++;
  process->param[0].ptr = get_param(process, vm->memory, IND_SIZE);
  process->param[0].size = IND_SIZE;
  process->active = true;
  process->delay = 2 - 1;
  return (cb_fork);
}
