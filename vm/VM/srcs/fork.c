/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 13:58:08 by thallot           #+#    #+#             */
/*   Updated: 2019/11/18 13:58:09 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

// static void			cb_fork(void *pvm, void *pproc)
// {
// 	t_env		*vm;
// 	t_process	*process;
// 	int i;
//
//   i = 0;
// 	vm = (t_env*)pvm;
// 	process = (t_process*)pproc;
//   if (create_process(vm))
// 		write(2, "Malloc error\n", 13);
//   printf("OLD PROCESSEUR : %d | CARRY : %d | R0 : %d\n", process->pc, process->carry, *(int*)process->records[0]);
//   vm->player->process.carry  = process->carry;
//   while (i++ <= 15)
//     ft_memcpy(vm->player->process.records[i], process->records[i], 4);
//   vm->player->process.pc = change_endian(process->param[0].ptr, 2);
//   printf("Creation d'un processeur en %d | Carry : %d | R0 : %d\n", vm->player->process.pc, vm->player->process.carry, *(int *)vm->player->process.records[0]);
// }
//
// t_result		ft_fork(t_env *vm, t_process *process)
// {
//   printf("ENTER FORK\n");
//   process->pc++;
//   process->param[0].ptr = get_param(process, vm->memory, IND_SIZE);
//   ft_printf("FORK : param = %d\n", change_endian(process->param[0].ptr, 2));
//   process->param[0].size = IND_SIZE;
//   process->active = true;
//   process->delay = 2 - 1;
//   return (cb_fork);
// }
