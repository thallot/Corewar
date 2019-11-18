/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or_xor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 14:42:55 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/14 14:43:00 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Callback retourné par "and" representant l'instruction a executer post delay
*/

static void		cb_and(void *pvm, void *pproc)
{
	int			arg;
	int			id;
	t_env		*vm;
	t_process	*process;

	process = (t_process*)pproc;
	vm = (t_env*)pvm;
	arg = change_endian(process->param[0].ptr, process->param[0].size);
	ft_printf("CB_LIVE : arg = %d\n", arg);
	if ((id = in_arraynb(arg, &vm->tab_champ)) != UNDEF)
	{
		ft_printf("Player %d(%s) is alive\n", vm->tab_champ.champs[id].num
				, vm->tab_champ.champs[id].name);
		if (vm->lastlive == UNDEF || id != vm->lastlive)
			vm->nblive++;
		vm->lastlive = id;
		process->state = alive;
	}
}

/*
**un appel a live n'est reussi que si les 4 octets suivant le pc correspondent
**bien a un champion, auquel cas ce champion sera considere comme en vie pendant
**ce CTD
**Un appel a live modifie la variable de la vm nblive uniquement si lastlive
**est undefined ou bien que l'id du champion ayant fait appel a live est
**different du dernier
*/

/*
**
**
**
**
**
**
*/

t_result		ft_and(t_env *vm, t_process *process)
{
	unsigned char	*mem;
	int				start;
	start = process->pc;
	mem = vm->memory;
	// process->pc++;
	if (get_params(process, mem, 3, false))
		return (NULL);
	if (process->param[0].type == UNDEF || process->param[1].type == UNDEF || process->param[2].type == UNDEF)
		return (NULL);
	printf("P0 %d | P1 %d | P2 %d\n", process->param[0].type, process->param[1].type, process->param[2].type);
	process->param[0].size = REG_SIZE;
	ft_printf("AND : param = %d\n", change_endian(process->param[0].ptr, REG_SIZE));
	process->active = true;
	process->delay = 10 - 1;
	return (cb_and);
}
