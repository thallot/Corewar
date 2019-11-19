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
** CALLBACK LDI
** additionne les valeurs effectives des deux premiers parametres
** en deduit une addresse et charge dans le registre (param3) les 4
** octets se trouvant a l'addrese trouvée
*/

static void			cb_ldi(void *pvm, void *pproc)
{
    t_process	*process;
    int         idx;
    int         address;
    void		*dest;
    unsigned char *mem;

    process = (t_process*)pproc;
    mem = ((t_env*)pvm)->memory;
    address = process->param[0].value + process->param[1].value;
    idx = change_endian(&mem[get_adress(0, address, false)], 4);
    dest = process->records[process->param[2].value - 1];
    ft_memcpy(dest, (void*)&idx, REG_SIZE);
    ft_printf("What's in the register after LDI? -> %d\n", *(int*)process->records[process->param[2].value - 1]);
}

/*
** remplace les valeurs initiales des parametres par leur valeur effective
** en se basant sur leur type
*/

void            set_param_values(unsigned char *mem, t_process *process)
{
    unsigned char   *idx;
    int             start;

    start = process->pc;
    if (process->param[0].type == IND_CODE)
    {
        idx = &mem[get_adress(start, process->param[0].value, false)];
        process->param[0].value = change_endian(idx, REG_SIZE);
        //ligne ci-dessous necessaire?
        process->param[0].size = REG_SIZE;
    }
    else if (process->param[0].type == REG_CODE)
    {
        process->param[0].value = *(int*)process->records[process->param[0].value - 1];
        //ligne ci-dessous necessaire?
        process->param[0].size = REG_SIZE;
    }
    if (process->param[1].type == REG_CODE)
    {
        process->param[1].value = *(int*)process->records[process->param[1].value - 1];
        // ligne ci-dessous necessaire?
        process->param[1].size = REG_SIZE;
    }
}

/*
** prend 3 parametres -> les deux premiers sont adittionés.
** Leur somme représente une adresse en memoire dans la VM.
** Les 4 octets situés a l'adresse trouvée sont stockés dans le
** registre indiqué en 3eme paramètre
** ici on parse, et on recupere les valeurs "effectives" des premiers params
*/

t_result		ft_ldi(t_env *vm, t_process *process)
{
    unsigned char	*mem;

    printf("ENTER LDI\n");
    mem = vm->memory;
    ft_printf("PC = %c", mem[process->pc]);
    if (get_params(process, mem, 3, true))
        return (NULL);
    if (process->param[2].size != T_REG || process->param[1].size == T_IND)
        return (NULL);
    set_param_values(mem, process);
    process->active = true;
    process->delay = 25 - 1;
    return (cb_ldi);
}
