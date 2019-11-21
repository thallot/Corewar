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

t_result		ft_lldi(t_env *vm, t_process *process)
{
    unsigned char	*mem;

    // printf("ENTER LDI\n");
    mem = vm->memory;
    if (get_params(process, mem, 3, true))
        return (NULL);
    if (process->param[2].type != T_REG || process->param[1].type == T_IND)
        return (NULL);
    set_param_values(mem, process);
    process->carry = !process->carry;
    process->active = true;
    process->delay = 50 - 1;
    return (cb_lldi);
}
