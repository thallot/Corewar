/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 15:02:09 by thallot           #+#    #+#             */
/*   Updated: 2019/11/14 15:02:10 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
** for now trying to have it work with indirect and direct for param 1, later about reg as 1st param
*/

static void			cb_ldi(void *pvm, void *pproc)
{
    t_env		*vm;
    t_process	*process;
    unsigned char *idx;
    int         param[2];
    int         address;
    void		*dest;
    unsigned char *mem;
    int         start;


    vm = (t_env*)pvm;
    process = (t_process*)pproc;
    start = process->pc;
    mem = vm->memory;
    // ci-dessous ajouter des variations en fonction du type (REG/IND/DIR) atm on imagine que ce sont des DIR2
    param[0] = process->param[0].value;
    param[1] = process->param[1].value;
    address = process->param[0].value + process->param[1].value;
    idx = &mem[get_adress(start, address, false)];
    ft_printf("param[0] = %d\n", process->param[0].value);
    ft_printf("param[1] = %d\n", process->param[1].value);
    ft_printf("address = %d\n", address);
    dest = process->records[process->param[2].value];
    ft_memcpy(dest, idx, REG_SIZE);
    ft_printf(" P0 : %d | P1:  %d\n", param[0], param[1]);
    ft_printf("r2 contient : %s\n", process->records[1]);
}

t_result		ft_ldi(t_env *vm, t_process *process)
{
    unsigned char	*mem;
    int				start;

    printf("ENTER LDI\n");
    start = process->pc;
    mem = vm->memory;
    if (get_params(process, mem, 3, true))
        return (NULL);
    if (process->param[2].size != T_REG || process->param[1].size == T_IND)
        return (NULL);
    process->active = true;
    process->delay = 25 - 1;
    return (cb_ldi);
}
