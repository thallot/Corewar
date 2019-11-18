/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:02:09 by thallot           #+#    #+#             */
/*   Updated: 2019/11/14 15:02:10 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void			cb_sti(void *pvm, void *pproc)
{
  t_env		*vm;
  t_process	*process;
  int param[3];
  int result;

  vm = (t_env*)pvm;
  process = (t_process*)pproc;
  param[0] = *(int*)process->records[process->param[0].value - 1];
  param[0] = change_endian(&(param[0]), 4);
  if (process->param[1].type == REG_CODE)
    param[1] = *(int*)process->records[process->param[1].value - 1];
  else
    param[1] = process->param[1].value;
  if (process->param[2].type == REG_CODE)
    param[2] = *(int*)process->records[process->param[2].value - 1];
  else
	 param[2] = process->param[2].value;
  result = param[1] + param[2];
  if (result != 0)
    result = result % 4096;
  else
  {
    result = 0;
    process->carry = !process->carry;
  }
  ft_memcpy((void*)&(vm->memory[result]), (void*)&param[0], 4);
  printf("P0 : %d | P1 : %d | P2:  %d\n", param[0], param[1], param[2]);
}

t_result		ft_sti(t_env *vm, t_process *process)
{
	unsigned char	*mem;
	int				start;

	start = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, true))
		return (NULL);
	if (process->param[0].type != REG_CODE)
		return (NULL);
  if (process->param[0].type == UNDEF || process->param[1].type == UNDEF || process->param[2].type == UNDEF)
  	return (NULL);
	process->active = true;
	process->delay = 25 - 1;
	return (cb_sti);
}
