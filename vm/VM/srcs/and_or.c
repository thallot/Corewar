/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 10:49:09 by thallot           #+#    #+#             */
/*   Updated: 2019/11/20 14:19:53 by jjaegle          ###   ########.fr       */
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
	int			i;
	int			param[3];

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	i = 0;
	while (i < 2)
	{
		if (process->param[i].type == T_REG)
			param[i] = *(int*)process->records[process->param[i].value - 1];
		else
			param[i] = process->param[i].value;
		i++;
	}
	param[2] = param[0] & param[1];
	ft_memcpy(process->records[process->param[2].value - 1], &param[2]
			, REG_SIZE);
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
	int				i;

	mem = vm->memory;
	process->pc_instru = process->pc;
	i = -1;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[2].type != T_REG)
		return (NULL);
	while (++i < 2)
		if (process->param[i].type == IND_CODE)
		{
			idx = &mem[get_adress(process->pc_instru, process->param[i].value
					, false)];
			process->param[i].ptr = (char*)idx;
			process->param[i].value = change_endian(idx, REG_SIZE);
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
	int			i;
	int param[3];

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	i = 0;
	while (i < 2)
	{
		if (process->param[i].type == T_REG)
			param[i] = *(int*)process->records[process->param[i].value - 1];
		else
			param[i] = process->param[i].value;
		i++;
	}
	param[2] = param[0] | param[1];
	ft_memcpy(process->records[process->param[2].value - 1], (void*)&param[2]
			, REG_SIZE);
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
	int				i;

	process->pc_instru = process->pc;
	mem = vm->memory;
	i = -1;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[2].type != T_REG)
		return (NULL);
	while (++i < 2)
		if (process->param[i].type == IND_CODE)
		{
			idx = &mem[get_adress(process->pc_instru, process->param[1].value
					, false)];
			process->param[i].ptr = (char*)idx;
			process->param[i].value = change_endian(idx, REG_SIZE);
		}
	process->active = true;
	process->delay = 6 - 1;
	return (cb_or);
}
