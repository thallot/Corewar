/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:28:29 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/14 15:32:13 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Callback retourner par live representant l'instruction a executer post delay
*/

static void		cb_live(void *pvm, void *pproc)
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

t_result		ft_live(t_env *vm, t_process *process)
{
	process->pc++;
	process->param[0].ptr = get_param(process, vm->memory, REG_SIZE);
	process->param[0].size = REG_SIZE;
	ft_printf("LIVE : param = %d\n", change_endian(process->param[0].ptr, REG_SIZE));
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

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	dest = process->records[process->param[1].value];
	ft_memcpy(dest, process->param[0].ptr, REG_SIZE);
	ft_printf("r%d = %d, carry = %d\n", process->param[1].value, process->param[0].value, process->carry);
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
	unsigned char	*idx;
	int				start;

	start = process->pc;
	mem = vm->memory;
	if(get_params(process, mem, 2, false))
		return (NULL);
	if (process->param[1].size != T_REG || process->param[0].size == T_REG)
		return (NULL);
	if (process->param[0].size == IND_SIZE)
	{
		idx = &mem[get_adress(start, process->param[0].value, false)];
		ft_printf("adress = %d\n",get_adress(start, process->param[0].value, false));
		process->param[0].ptr = (char*)idx;
		process->param[0].value = change_endian(idx, REG_SIZE);
		process->param[0].size = REG_SIZE;
		ft_printf("LD : value = %d\n", process->param[0].value);
	}
	if (!process->param[0].value)
		process->carry = !process->carry;
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

t_result	ft_st(t_env *vm, t_process *process)
{
	unsigned char	*memory;
	unsigned char	*dest;
	int				start;

	start = process->pc;
	memory = vm->memory;
	if(get_params(process, memory, 2, false))
		return (NULL);
	if (process->param[0].size != T_REG || process->param[1].size == DIR_SIZE)
		return (NULL);
	if (process->param[1].size == T_REG)
		dest = (unsigned char *)process->records[process->param[1].value];
	else
		dest = &memory[get_adress(start, process->param[1].value, false)];
	if (process->param[1].size == T_REG)
		ft_printf("ST : dest = registre %d\n", process->param[1].value);
	else
		ft_printf("ST : dest = decallage :%d\n", get_adress(start, process->param[1].value, false));
	process->param[1].ptr = (char*)dest;
	process->active = true;
	process->delay = 5 - 1;
	return (cb_st);
}
/*
void		ft_add(t_env *vm, t_process *process)
{
	unsigned char	encoded;
	unsigned char	*memory;
	int				src;
	int				params[3];

	memory = vm->memory;
	encoded = get_encoded(process, memory);
	params[0] = get_param(process, memory, get_size(encoded, FIRST));
	params[1] = get_param(process, memory, get_size(encoded, SECND));
	params[2] = get_param(process, memory, get_size(encoded, THIRD));
	if (!is_register(params, 3))
		return ;
	src = val_record(process, params[0], READ)
		+ val_record(process, params[1], READ);
	ft_memcpy(process->records[params[2] - 1], &src, REG_SIZE);
	if (!*(int*)process->records[params[2] - 1])
		process->carry = !process->carry;
	ft_printf("resultat = %d, carry = %d\n", *(int*)process->records[params[2] - 1], process->carry);
}
*/