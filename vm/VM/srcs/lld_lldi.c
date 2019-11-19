/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lld_lldi.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edillenb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 16:17:40 by edillenb          #+#    #+#             */
/*   Updated: 2019/11/18 16:17:44 by edillenb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "vm.h"

/*
** for now trying to have it work with indirect and direct for param 1, later about reg as 1st param
*/

static void			cb_lldi(void *pvm, void *pproc)
{
    t_process	*process;
    int         idx;
    int         address;
    void		*dest;
    unsigned char *mem;

    process = (t_process*)pproc;
    mem = ((t_env*)pvm)->memory;
    address = process->param[0].value + process->param[1].value;
    idx = change_endian(&mem[get_adress(0, address, true)], 4);
    dest = process->records[process->param[2].value - 1];
    ft_memcpy(dest, (void*)&idx, REG_SIZE);
    // ft_printf("What's in the register after LLDI? -> %d\n", *(int*)process->records[process->param[2].value - 1]);
}

void            set_param_values(unsigned char *mem, t_process *process)
{
    unsigned char   *idx;
    int             start;

    start = process->pc;
    if (process->param[0].type == IND_CODE)
    {
        idx = &mem[get_adress(start, process->param[0].value, true)];
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

t_result		ft_lldi(t_env *vm, t_process *process)
{
    unsigned char	*mem;

    // printf("ENTER LDI\n");
    mem = vm->memory;
    if (get_params(process, mem, 3, true))
        return (NULL);
    if (process->param[2].size != T_REG || process->param[1].size == T_IND)
        return (NULL);
    set_param_values(mem, process);
    process->carry = !process->carry;
    process->active = true;
    process->delay = 50 - 1;
    return (cb_lldi);
}
