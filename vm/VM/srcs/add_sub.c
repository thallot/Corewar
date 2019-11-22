/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/13 16:32:27 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/21 18:30:21 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void			cb_st(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	void		*src;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	src = process->records[process->param[0].value - 1];
	ft_memrev(src, REG_SIZE);
	ft_memcpy(process->param[1].ptr, src, REG_SIZE);
	write_in_visu(process->pc_instru, (int)src, vm);
}

static void			cb_add(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	int			registre[3];

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	registre[0] = *(int *)process->records[process->param[0].value - 1];
	registre[1] = *(int *)process->records[process->param[1].value - 1];
	registre[2] = registre[0] + registre[1];
	ft_memcpy(process->records[process->param[2].value - 1]
			, (void*)&registre[2], REG_SIZE);
	process->carry = registre[2] == 0 ? 1 : 0;
}

t_result		ft_add(t_env *vm, t_process *process)
{
	unsigned char	*mem;

	process->pc_instru = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[0].type != T_REG || process->param[1].type != T_REG
			|| process->param[2].type != T_REG)
		return (NULL);
	process->active = true;
	process->delay = 10 - 1;
	return (cb_add);
}

static void			cb_sub(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	int			registre[3];

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	registre[0] = *(int *)process->records[process->param[0].value - 1];
	registre[1] = *(int *)process->records[process->param[1].value - 1];
	registre[2] = registre[0] - registre[1];
	ft_memcpy(process->records[process->param[2].value - 1]
			, (void*)&registre[2], REG_SIZE);
	process->carry = registre[2] == 0 ? 1 : 0;
}

t_result		ft_sub(t_env *vm, t_process *process)
{
	unsigned char	*mem;

	process->pc_instru = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[0].type != T_REG || process->param[1].type != T_REG
			|| process->param[2].type != T_REG)
		return (NULL);
	process->active = true;
	process->delay = 10 - 1;
	return (cb_sub);
}
