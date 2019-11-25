/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xor_zjmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 12:05:18 by thallot           #+#    #+#             */
/*   Updated: 2019/11/22 18:05:12 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** Effectue un ^ binaire entre les 2 premiers parametres,
** et stock le resultat dans le 3e parametre aui est un registre.
** les 2 premier parametre sont code sur 2 octets
*/

static void		cb_xor(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	int			res;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	set_param_value(vm->memory, process, 1, false);
	set_param_value(vm->memory, process, 2, false);
	res = process->param[0].value ^ process->param[1].value;
	ft_memcpy(process->records[process->param[2].value - 1], &res, REG_SIZE);
	process->carry = res == 0 ? true : false;
}

/*
** XOR prends en parametre T_REG | T_DIR | T_IND, T_REG | T_IND | T_DIR, T_REG
*/

t_result		ft_xor(t_env *vm, t_process *process)
{
	unsigned char	*mem;

	process->pc_instru = process->pc;
	mem = vm->memory;
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

static void		cb_zjmp(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	int			address;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	if (process->carry == false)
		return ;
	address = get_adress(process->pc_instru, process->param[0].value, false);
	process->pc = address;
}

/*
**zjmp lit 2 octets suivant l'instruction et retourne sa callback
*/

t_result		ft_zjmp(t_env *vm, t_process *process)
{
	process->pc_instru = process->pc;
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, IND_CODE, false);
	process->param[0].value = (short int)change_endian(process->param[0].ptr
			, IND_SIZE);
	process->active = true;
	process->delay = 20 - 1;
	return (cb_zjmp);
}
