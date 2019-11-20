// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   ldi.c                                              :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2019/11/14 15:02:09 by thallot           #+#    #+#             */
// /*   Updated: 2019/11/14 15:02:10 by thallot          ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "vm.h"

// /*
// ** STI additionne la valeur des deux dernier parametres (p1 et p2),
// ** et ecrit le contenue du registre passe en parametre (p0) a ladresse resultante
// ** de la somme de p1 et p2
// ** Si le p1 est un indirect,
// ** on va chercher la valeur present a p1.value + pc_instru
// ** Dans tous les cas on additionne la valeur de p1 et p2
// ** Puis on va a l addresse resultante de cette somme,
// ** et on y ecrit la valeur contenue dans le registre passe en parametre 0 (p0)
// */

// static void			cb_sti(void *pvm, void *pproc)
// {
//   t_env		*vm;
//   t_process	*process;
//   int param[3];
//   int result;

//   vm = (t_env*)pvm;
//   process = (t_process*)pproc;
//   printf("PROCESS : %d \n", process->pc);
//   param[0] = *(int*)process->records[process->param[0].value - 1];
//   printf("REG VALUE : %d\n", param[0]);
//   param[0] = change_endian((void *)&param[0], 4);
//   if (process->param[1].type == REG_CODE)
//     param[1] = *(int*)process->records[process->param[1].value - 1];
//   else
//     param[1] = process->param[1].value;
//   if (process->param[2].type == REG_CODE)
//     param[2] = *(int*)process->records[process->param[2].value - 1];
//   else
// 	 param[2] = process->param[2].value;
//   result = param[1] + param[2];
//   ft_printf("result = %d\n", result);
//   if (result != 0)
//     result = result % 4096;
//   else
//   {
//     result = 0;
//     process->carry = !process->carry;
//   }
//   ft_memcpy((void*)&(vm->memory[result]), (void*)&param[0], 4);
//   printf("P0 : %d | P1 : %d | P2:  %d\n", param[0], param[1], param[2]);
//   ft_printf("JUST wrote : %d at address: %d\n", change_endian(&vm->memory[result], 4), change_endian(&param[0], 4));
// }

// /*
// ** STI prends en parametre T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG
// */

// t_result		ft_sti(t_env *vm, t_process *process)
// {
// 	unsigned char	*mem;
//   unsigned char	*idx;

//   printf("ENTER STI\n");
// 	process->pc_instru = process->pc;
// 	mem = vm->memory;
// 	if (get_params(process, mem, 3, true))
// 		return (NULL);
// 	if (process->param[0].type != REG_CODE || process->param[2].type == IND_CODE)
// 		return (NULL);
//   if (process->param[0].type == UNDEF || process->param[1].type == UNDEF || process->param[2].type == UNDEF)
//   	return (NULL);
//   printf("NO EXIT \n");
//   if (process->param[1].type == IND_CODE)
//   {
//     idx = &mem[get_adress(process->pc_instru, process->param[1].value, false)];
// 		process->param[1].value = change_endian(idx, REG_SIZE);
// 		process->param[1].size = REG_SIZE;
//     printf(" IND VALUE : %d\n", process->param[1].value);
//   }
// 	process->active = true;
// 	process->delay = 25 - 1;
// 	return (cb_sti);
// }
