/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 15:33:25 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/25 15:59:45 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

/*
**Les processeurs sont stockes dans la VM sous forme de liste, t_listp, chaque
**nouveau process est mis en tete de liste de maniere a ce que le dernier
**cree sois le premier a jouer.
*/

/*
**les processeurs sont crees pour chaque processus joueur, ils representent
**l'environnement mis a disposition du processus pour jouer avec les registres
**le PC et le carry.
**un processeur peut etre actif ou non, il s'active l'orsque le pc rencontre
**un opcode, quand il est actif il ne se deplace plus dans la memoire le temps
**, delay, qu'il realise son operation.
*/

/*
**add_player cree un nouveau maillon processeur, le place en tete de liste et
**retourne la nouvelle liste.
*/

static t_listp	*add_player(t_info_champ *champ, t_listp *al)
{
	t_listp	*ret;

	ret = NULL;
	if (!(ret = ft_memalloc(sizeof(t_listp))))
		return (NULL);
	ft_memcpy(ret->process.records[0], &champ->num, sizeof(champ->num));
	ret->process.carry = false;
	ret->next = al;
	return (ret);
}

/*
**create_process est appele juste avant de commencer le jeu apres la reception
**de tout les champions elle va creer les premiers process des joueurs.
*/

int				create_process(t_env *vm)
{
	int			i;
	int			j;
	t_tabchamp	tab;
	int			start;

	tab = vm->tab_champ;
	i = 0;
	start = 0;
	while (i < tab.nb_champ)
	{
		if (!(vm->player = add_player(&tab.champs[i], vm->player)))
			return (EXIT_FAILURE);
		vm->player->process.pc = start;
		vm->player->process.active = false;
		ft_memcpy(&vm->memory[start], tab.champs[i].instr, CHAMP_MAX_SIZE);
		j = start;
		while (j < start + tab.champs[i].size)
		{
			vm->memory_visu[j] = (i + 1) * 100;
			j++;
		}
		start += MEM_SIZE / tab.nb_champ;
		i++;
	}
	return (EXIT_SUCCESS);
}
