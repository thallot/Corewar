/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:49:09 by thallot           #+#    #+#             */
/*   Updated: 2019/11/15 10:49:15 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Effectue un & binaire entre les 2 premiers parametres,
** et stock le resultat dans le 3e parametre aui est un registre.
** les 2 premier parametre sont code sur 2 octets
*/
static void			cb_and(void *pvm, void *pproc)
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
  param[2] = param[0] & param[1];
  ft_memcpy(process->records[process->param[2].value - 1], (void*)&param[2], REG_SIZE);
  if (!param[2])
		process->carry = !process->carry;
	ft_printf("AND | Param0 : %d | Param1 : %d\n", param[0], param[1]);
  ft_printf("AND RESULT : %d \n", *(int*)process->records[process->param[2].value - 1]);
}

/*
** AND prends en parametre T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
*/
t_result		ft_and(t_env *vm, t_process *process)
{
	unsigned char	*mem;
	unsigned char	*idx;

	mem = vm->memory;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[0].type == UNDEF || process->param[1].type == UNDEF || process->param[2].type == UNDEF)
		return (NULL);
	if (process->param[2].size != T_REG)
		return (NULL);
	if (process->param[0].type == IND_CODE)
	{
		idx = &mem[get_adress(process->pc_instru, process->param[1].value, false)];
		process->param[0].ptr = (char*)idx;
		process->param[0].value = change_endian(idx, REG_SIZE);
		process->param[0].size = REG_SIZE;
	}
	if (process->param[1].type == IND_CODE)
	{
		idx = &mem[get_adress(process->pc_instru, process->param[1].value, false)];
		process->param[1].ptr = (char*)idx;
		process->param[1].value = change_endian(idx, REG_SIZE);
		process->param[1].size = REG_SIZE;
	}
	process->active = true;
	process->delay = 6 - 1;
	return (cb_and);
}

/*
** Effectue un | binaire entre les 2 premiers parametres,
** et stock le resultat dans le 3e parametre aui est un registre.
** les 2 premier parametre sont code sur 2 octets
*/
static void			cb_or(void *pvm, void *pproc)
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
  param[2] = param[0] | param[1];
  ft_memcpy(process->records[process->param[2].value - 1], (void*)&param[2], REG_SIZE);
  if (!param[2])
		process->carry = !process->carry;
	ft_printf("OR | Param0 : %d | Param1 : %d\n", param[0], param[1]);
  ft_printf("OR RESULT : %d \n", *(int*)process->records[process->param[2].value - 1]);
}

/*
** OR prends en parametre T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
*/
t_result		ft_or(t_env *vm, t_process *process)
{
	unsigned char	*mem;
	unsigned char	*idx;
	int				start;

	start = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[2].size != T_REG)
		return (NULL);
	if (process->param[0].type == IND_CODE)
	{
		idx = &mem[get_adress(process->pc_instru, process->param[1].value, false)];
		process->param[0].ptr = (char*)idx;
		process->param[0].value = change_endian(idx, REG_SIZE);
		process->param[0].size = REG_SIZE;
	}
	if (process->param[1].type == IND_CODE)
	{
		idx = &mem[get_adress(process->pc_instru, process->param[1].value, false)];
		process->param[1].ptr = (char*)idx;
		process->param[1].value = change_endian(idx, REG_SIZE);
		process->param[1].size = REG_SIZE;
	}
	process->active = true;
	process->delay = 6 - 1;
	return (cb_or);
}
