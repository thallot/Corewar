/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_sti.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 17:27:02 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/29 11:59:13 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** CALLBACK LDI
** additionne les valeurs effectives des deux premiers parametres
** en deduit une addresse et charge dans le registre (param3) les 4
** octets se trouvant a l'addrese trouvée
*/

static void			cb_ldi(void *pvm, void *pproc)
{
	t_process		*process;
	int				address;
	void			*dest;
	unsigned char	*mem;
	int				lg;

	process = (t_process*)pproc;
	mem = ((t_env*)pvm)->memory;
	lg = (mem[process->pc_instru] == 10) ? false : true;
	set_param_value(mem, process, 1, lg);
	set_param_value(mem, process, 2, lg);
	address = (short)process->param[0].value + (short)process->param[1].value;
	address = change_endian(&mem[get_adress(process->pc_instru
				, address % IDX_MOD, lg)], REG_SIZE);
	dest = process->records[process->param[2].value - 1];
	ft_memcpy(dest, (void*)&address, REG_SIZE);
	if (lg == true && !(*(int*)dest))
		process->carry = 1;
	else if (lg == true)
		process->carry = 0;
}

/*
** prend 3 parametres -> les deux premiers sont adittionés.
** Leur somme représente une adresse en memoire dans la VM.
** Les 4 octets situés a l'adresse trouvée sont stockés dans le
** registre indiqué en 3eme paramètre
** ici on parse, et on recupere les valeurs "effectives" des premiers params
*/

t_result			ft_ldi(t_env *vm, t_process *process)
{
	unsigned char	*mem;

	process->pc_instru = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, true))
		return (NULL);
	if (process->param[2].type != REG_CODE
			|| process->param[1].type == IND_CODE)
		return (NULL);
	process->active = true;
	process->delay = 25 - 1;
	return (cb_ldi);
}

/*
** STI additionne la valeur des deux dernier parametres (p1 et p2),
** et ecrit le contenue du registre passe en parametre (p0) a ladresse
** resultante de la somme de p1 et p2
** Si le p1 est un indirect,
** on va chercher la valeur present a p1.value + pc_instru
** Dans tous les cas on additionne la valeur de p1 et p2
** Puis on va a l addresse resultante de cette somme,
** et on y ecrit la valeur contenue dans le registre passe en parametre 0 (p0)
*/

static void			cb_sti(void *pvm, void *pproc)
{
	t_env			*vm;
	t_process		*process;
	unsigned char	*mem;
	int				address;
	int				reg;

	vm = (t_env*)pvm;
	process = (t_process*)pproc;
	mem = vm->memory;
	set_param_value(mem, process, 2, false);
	set_param_value(mem, process, 3, false);
	address = process->param[1].value + process->param[2].value;
	address = get_adress(process->pc_instru, address, false);
	reg = change_endian(&process->records[process->param[0].value - 1]
			, REG_SIZE);
	ft_memcpy(&(vm->memory[address]), &reg, REG_SIZE);
	write_in_visu(process->pc_instru, address, vm);
}

/*
** STI prends en parametre T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG
*/

t_result			ft_sti(t_env *vm, t_process *process)
{
	unsigned char	*mem;

	process->pc_instru = process->pc;
	mem = vm->memory;
	if (get_params(process, mem, 3, true))
		return (NULL);
	if (process->param[0].type != REG_CODE
			|| process->param[2].type == IND_CODE)
		return (NULL);
	process->active = true;
	process->delay = 25 - 1;
	return (cb_sti);
}
