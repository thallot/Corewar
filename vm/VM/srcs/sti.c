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
  int param[2];

  vm = (t_env*)pvm;
  process = (t_process*)pproc;
  param[0] = change_endian(&(process->param[0].value), 2);
	param[1] = change_endian(&(process->param[1].value), 2);
  printf(" P0 : %d | P1:  %d\n", param[0], param[1]);
}

t_result		ft_sti(t_env *vm, t_process *process)
{
	unsigned char	*mem;
	int				start;

	start = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[0].size != T_REG)
		return (NULL);
	process->active = true;
	process->delay = 25 - 1;
	return (cb_ldi);
}
