/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:05:18 by thallot           #+#    #+#             */
/*   Updated: 2019/11/20 11:47:42 by jjaegle          ###   ########.fr       */
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
	int			i;
	int			res;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	i = 0;
	set_param_value(vm->memory, process, 1);
	set_param_value(vm->memory, process, 2);
	res = process->param[0].value ^ process->param[1].value;
	ft_memcpy(process->records[process->param[2].value - 1], &res, REG_SIZE);
	process->carry = res == 0 ? 1 : 0;
	ft_printf("XOR | Param0 : %d | Param1 : %d\n", process->param[0].value, process->param[1].value);
	ft_printf("XOR RESULT : %d \n", *(int*)process->records[process->param[2].value - 1]);
}

/*
** XOR prends en parametre T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
*/

t_result		ft_xor(t_env *vm, t_process *process)
{
	unsigned char	*mem;
	int				i;

	process->pc_instru = process->pc;
	mem = vm->memory;
	i = -1;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[2].type != T_REG)
		return (NULL);
	process->active = true;
	process->delay = 6 - 1;
	return (cb_xor);
}

/*
** Saute jusqu a l adresse passée en parametre
** Si result >= 4095 l address est surement negative,
** et fais reference a un label.
*/
static void			cb_zjmp(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	int			address;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	address = change_endian(process->param[0].ptr, IND_SIZE);
	printf(" address : %d\n", address);
	printf(" address VALUE : %d\n", process->param[0].value);
	printf(" process instru : %d\n", process->param[0].value);
	address = get_adress(process->pc_instru, process->param[0].value, false);
	printf(" address : %d\n", address);
	process->pc = address;
	ft_printf("ZJMP Result : %d \n", process->pc);
}

t_result		ft_zjmp(t_env *vm, t_process *process)
{
	process->pc_instru = process->pc;
	process->pc++;
	if (process->carry == true)
	{
		process->param[0].ptr = get_param(process, vm->memory, IND_CODE, false);
		process->param[0].value = (short int)change_endian(process->param[0].ptr
				, IND_SIZE);
		process->active = true;
		process->delay = 20 - 1;
	  	return (cb_zjmp);
	}
	return (NULL);
}
