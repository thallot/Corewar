/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:23:02 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/22 17:01:20 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static void		initialise_rules(t_rules *rules, t_env *vm, t_visu *visu)
{
	ft_bzero(rules, sizeof(t_rules));
	rules->cycle_to_die = CYCLE_TO_DIE;
	rules->someone_alive = true;
	vm->rules = rules;
	if (vm->visu)
		init_visu(visu, rules, vm, vm->player);
}

/*
**check_nbr_live applique les regles lies a la reduction de CTD
**Si entre 2 verif il y a eu NBR_LIVE de live alors CTD decroit
**Sinon si depuis MAX_CHECKS verif CTD n'a pas bouger, il decroit.
*/

static void		check_nbr_lives(t_rules *rules, t_env *vm)
{
	int i;

	i = 0;
	if (vm->cmpt_live >= NBR_LIVE || rules->nb_check == MAX_CHECKS)
	{
		rules->cycle_to_die -= CYCLE_DELTA;
		if (rules->cycle_to_die <= 0)
			rules->cycle_to_die = 1;
		rules->nb_check = 0;
		while (i < 4)
		{
			vm->live[i] = 0;
			vm->nb_live[i] = 0;
			i++;
		}
	}
	else
		rules->nb_check++;
	vm->cmpt_live = 0;
}

/*
**print_result affiche le resultat de la partie, si aucun player n'as ete
**declare en vie durant ce CTD c'est un match nul et il n'y a que des perdants
**Si il restait un survivant lors de la derniere verif alors il est le vainqueur
*/

static void		print_result(t_info_champ champs[], int *ll, int nblive
		, t_rules *rules)
{
	int		i;

	(void)champs;
	(void)nblive;
	i = *ll;
	if (nblive == 1)
		ft_printf("le joueur %d(%s) a gagne\n", champs[i].num, champs[i].name);
	else
		ft_printf("No winner for today... Only looser\n");
	rules->someone_alive = false;
}

/*
**whos_living est appele tout les CTD, fais le tour des players et verifie
**leurs etats s'ils sont en vie, ils sont mis en attente jusqu'a la prochaine
**verif, sinon ils sont consideres comme mort.
**Le respect des regles est verifier grace a check_nbr_lives et la fin de la
**partie par print_result.
*/

static void		whos_living(t_listp *players, t_env *vm, t_rules *rules)
{
	t_listp	*p;

	rules->cr_cycle = 0;
	p = players;
	while (players)
	{
		if (players->process.state == alive)
			players->process.state = waiting;
		else if (players->process.state == waiting)
			players->process.state = dead;
		players = players->next;
	}
	if (nb_alive(p))
		check_nbr_lives(rules, vm);
	else if (!vm->visu)
		print_result(vm->tab_champ.champs, &vm->lastlive, vm->nblive, rules);
	if (vm->nblive > 1)
	{
		vm->nblive = 0;
		vm->lastlive = UNDEF;
	}
}

/*
**lets_play fais tourner le jeu cycle apres cycle et veille grace a whos living
**et au variable contenue dans rules a ce que les regles soit respectes.
*/

void			lets_play(t_env *vm)
{
	t_rules			rules;
	t_visu			visu;

	initialise_rules(&rules, vm, &visu);
	while (rules.someone_alive == true && (int)rules.cycle != vm->dump
		&& ((vm->visu && (!rules.cycle || visu.pause == 0)) || !vm->visu))
	{
		if (vm->visu)
		{
			visu.process = vm->player;
			visu_core(&visu, 0);
		}
		process_play(vm->player, vm);
		rules.cycle++;
		if (++rules.cr_cycle == rules.cycle_to_die)
			whos_living(vm->player, vm, &rules);
	}
	if (vm->visu)
		del_visu(&visu);
	else if ((int)rules.cycle == vm->dump)
		dump_memory(vm->memory);
}
