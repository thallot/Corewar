/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi_sti.c                                          :+:      :+:    :+:   */
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
    int         idx;
    int         address;
    void		*dest;
    unsigned char *mem;
    int         start;

    vm = (t_env*)pvm;
    process = (t_process*)pproc;
    start = process->pc;
    mem = vm->memory;
    address = process->param[0].value + process->param[1].value;
    idx = change_endian(&mem[get_adress(0, address, false)], 4);
    dest = process->records[process->param[2].value - 1];
    ft_memcpy(dest, (void*)&idx, REG_SIZE);
    ft_printf("What's in the register? -> %d\n", *(int*)process->records[process->param[2].value - 1]);
}

void            set_param_values(unsigned char *mem, t_process *process)
{
    unsigned char   *idx;
    int             start;

    start = process->pc;
    if (process->param[0].type == IND_CODE)
    {
        idx = &mem[get_adress(start, process->param[0]. value, false)];
        process->param[0].value = change_endian(idx, REG_SIZE);
        process->param[0].size = REG_SIZE;
    }
    else if (process->param[0].type == REG_CODE)
    {
        process->param[0].value = *(int*)process->records[process->param[0].value - 1];
        process->param[0].size = REG_SIZE;
    }
    if (process->param[1].type == REG_CODE)
    {
        process->param[1].value = *(int*)process->records[process->param[1].value - 1];
        process->param[1].size = REG_SIZE;
    }
}

t_result		ft_ldi(t_env *vm, t_process *process)
{
    unsigned char	*mem;

    printf("ENTER LDI\n");
    mem = vm->memory;
    if (get_params(process, mem, 3, true))
        return (NULL);
    if (process->param[2].size != T_REG || process->param[1].size == T_IND)
        return (NULL);
    set_param_values(mem, process);
    process->active = true;
    process->delay = 25 - 1;
    return (cb_ldi);
}
