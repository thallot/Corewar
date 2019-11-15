/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:05:18 by thallot           #+#    #+#             */
/*   Updated: 2019/11/15 12:05:19 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Effectue un ^ binaire entre les 2 premiers parametres,
** et stock le resultat dans le 3e parametre aui est un registre.
** les 2 premier parametre sont code sur 2 octets
*/
static void			cb_xor(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
  int param[3];

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
  if (process->param[0].size == T_REG)
    param[0] = *(int*)process->records[process->param[0].value - 1];
  else
    param[0] = process->param[0].value;
  if (process->param[1].size == T_REG)
    param[1] = *(int*)process->records[process->param[1].value - 1];
  else
    param[1] = process->param[1].value;
  param[2] = param[0] ^ param[1];
  ft_memcpy(process->records[process->param[2].value - 1], (void*)&param[2], REG_SIZE);
  if (!param[2])
		process->carry = !process->carry;
	ft_printf("XOR | Param0 : %d | Param1 : %d\n", param[0], param[1]);
  ft_printf("XOR RESULT : %d \n", *(int*)process->records[process->param[2].value - 1]);
}

t_result		ft_xor(t_env *vm, t_process *process)
{
	unsigned char	*mem;
	int				start;

	start = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[2].size != T_REG)
		return (NULL);
	process->active = true;
	process->delay = 6 - 1;
	return (cb_xor);
}

/*
*/
static void			cb_zjmp(void *pvm, void *pproc)
{
	(void)pvm;
  (void)pproc;

	result = change_endian(process->param[0].ptr, IND_SIZE) % 4096;
	ft_printf("ZJMP : param = %d\n", result);
}

t_result		ft_zjmp(t_env *vm, t_process *process)
{
	int result;

  // if (process->carry == true)
  // {
    process->pc++;
  	process->param[0].ptr = get_param(process, vm->memory, IND_SIZE);
  	process->param[0].size = IND_SIZE;

  	process->active = true;
  	process->delay = 2 - 1;
  	return (cb_zjmp);
  // }
  // else
  //   return (NULL);
}
