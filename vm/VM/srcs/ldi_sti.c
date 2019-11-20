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
** remplace les valeurs initiales des parametres par leur valeur effective
** en se basant sur leur type
*/

void            set_param_value(unsigned char *mem, t_process *process, int i)
{
    unsigned char   *idx;

    if (process->param[i - 1].type == IND_CODE)
    {
        idx = &mem[get_adress(process->pc_instru, (short)process->param[i - 1].value, false)];
        process->param[i - 1].value = change_endian(idx, REG_SIZE);
    }
    else if (process->param[i - 1].type == REG_CODE)
        process->param[i - 1].value = *(int*)process->records[(short)process->param[i - 1].value - 1];
    process->param[i - 1].size = REG_SIZE;
}

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
    set_param_value(mem, process, 1);
    set_param_value(mem, process, 2);
    address = process->param[0].value + process->param[1].value;
    idx = change_endian(&mem[get_adress(process->pc_instru, address, false)], REG_SIZE);
    dest = process->records[process->param[2].value - 1];
    ft_memcpy(dest, (void*)&idx, REG_SIZE);
    ft_printf("What's in the register after LDI? -> %d\n", *(int*)process->records[process->param[2].value - 1]);
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
    process->pc_instru = process->pc;
    mem = vm->memory;
    if (get_params(process, mem, 3, true))
        return (NULL);
    if (process->param[2].type != REG_CODE || process->param[1].type == IND_CODE)
        return (NULL);
    if (process->param[0].type == UNDEF || process->param[1].type == UNDEF || process->param[2].type == UNDEF)
        return (NULL);
    process->active = true;
    process->delay = 25 - 1;
    return (cb_ldi);
}

/*
** STI additionne la valeur des deux dernier parametres (p1 et p2),
** et ecrit le contenue du registre passe en parametre (p0) a ladresse resultante
** de la somme de p1 et p2
** Si le p1 est un indirect,
** on va chercher la valeur present a p1.value + pc_instru
** Dans tous les cas on additionne la valeur de p1 et p2
** Puis on va a l addresse resultante de cette somme,
** et on y ecrit la valeur contenue dans le registre passe en parametre 0 (p0)
*/

static void			cb_sti(void *pvm, void *pproc)
{
  t_env         *vm;
  t_process     *process;
  unsigned char *mem;
  int           address;
  int           reg;   
  int           idx;    

  vm = (t_env*)pvm;
  process = (t_process*)pproc;
  mem = vm->memory;
  set_param_value(mem, process, 2);
  set_param_value(mem, process, 3);
  address = process->param[1].value + process->param[2].value;
  idx = change_endian(&mem[get_adress(process->pc_instru, address, false)], REG_SIZE);
  reg = change_endian(&process->records[process->param[0].value - 1], REG_SIZE);
  ft_memcpy(&(vm->memory[idx]), &reg, REG_SIZE); 
  ft_printf("JUST WROTE THE FOLLOWING IN MEMORY : %d at address : %d\n", change_endian(&(vm->memory[idx]), 4), idx);
}


/*
** STI prends en parametre T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG
*/

t_result		ft_sti(t_env *vm, t_process *process)
{
    unsigned char	*mem;

    printf("ENTER STI\n");
    process->pc_instru = process->pc;
    mem = vm->memory;
    if (get_params(process, mem, 3, true))
        return (NULL);
    if (process->param[0].type != REG_CODE || process->param[2].type == IND_CODE)
        return (NULL);
    if (process->param[0].type == UNDEF || process->param[1].type == UNDEF || process->param[2].type == UNDEF)
    return (NULL);
    process->active = true;
    process->delay = 25 - 1;
    return (cb_sti);
}
