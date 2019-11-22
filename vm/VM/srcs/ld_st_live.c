/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:28:29 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/22 17:52:32 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Callback retourner par live representant l'instruction a executer post delay
*/

static void		cb_live(void *pvm, void *pproc)
{
	int			id;
	t_env		*vm;
	t_process	*process;

	process = (t_process*)pproc;
	vm = (t_env*)pvm;
	if ((id = in_arraynb(process->param[0].value, &vm->tab_champ)) != UNDEF)
	{
		if (vm->lastlive == UNDEF || id != vm->lastlive)
			vm->nblive++;
		vm->cmpt_live++;
		vm->lastlive = id;
		process->state = alive;
		if (!vm->visu)
			ft_printf("Joueur %d est en vie\n", process->param[0].value);
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

t_result		ft_live(t_env *vm, t_process *process)
{
	process->pc_instru = process->pc;
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, DIR_CODE, false);
	process->param[0].value = change_endian(process->param[0].ptr, REG_SIZE);
	process->active = true;
	process->delay = 10 - 1;
	return (cb_live);
}

/*
**Callback retourner par ld representant l'instruction a executer post delay
*/

static void		cb_ld(void *pvm, void *pproc)
{
	t_env		*vm;
	t_process	*process;
	void		*dest;
	int			lg;
	int			res;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	lg = (vm->memory[process->pc_instru] == 2) ? false : true;
	set_param_value(vm->memory, process, 1, lg);
	if (!process->param[0].value)
		process->carry = true;
	else
		process->carry = false;
	dest = process->records[process->param[1].value - 1];
	res = process->param[0].value;
	ft_memcpy(dest, (void *)&res, REG_SIZE);
}

/*
**permet de charger une valeure dans un de nos registres le premier parametre
**est un direct ou un indirect, le deuxieme est forcement un registre.
**on utilise un pointeur generique pour recuperer l'adresse ou charger notre
**registre, si p1 est un indirecte :
**on va remplir notre notre registre a  partir l'adresse
**(PC + P1 % IDX_MOD) % MEM_SIZE
**sinon on remplit notre registre avec les 4 octets suivant l'encodeur
**si p1 = 0, modifie le carry
*/

t_result		ft_ld(t_env *vm, t_process *process)
{
	unsigned char	*mem;

	process->pc_instru = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 2, false))
		return (NULL);
	if (process->param[1].type != T_REG || process->param[0].type == T_REG)
		return (NULL);
	process->active = true;
	process->delay = 5 - 1;
	return (cb_ld);
}

/*
**store la valeure du registre contenu dans p1 a l'adresse represente par p2
**si c'est un indirecte sinon dans le registre specifie. ca n'est jamais un
**direct.
**si c'est un registre un store d'un registre a un autre sans effectuer de
**memrev, sinon on se rend a ladresse (PC + p2 % IDX_MOD) % MEM_SIZE et on y
** charge le contenu du registre.
*/

t_result		ft_st(t_env *vm, t_process *process)
{
	unsigned char	*memory;
	unsigned char	*dest;
	int				start;

	process->pc_instru = process->pc;
	start = process->pc;
	memory = vm->memory;
	if (get_params(process, memory, 2, false))
		return (NULL);
	if (process->param[0].type != T_REG || process->param[1].type == DIR_CODE)
		return (NULL);
	if (process->param[1].type == T_REG)
		dest = (unsigned char *)process->records[process->param[1].value - 1];
	else
		dest = &memory[get_adress(start, process->param[1].value, false)];
	process->param[1].ptr = (char*)dest;
	process->active = true;
	process->delay = 5 - 1;
	return (cb_st);
}
