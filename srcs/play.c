/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   play.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:02:40 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/22 17:57:03 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_result		(*g_instr[NB_INSTR])(t_env *vm, t_process *process) =
{
	ft_live,
	ft_ld,
	ft_st,
	ft_add,
	ft_sub,
	ft_and,
	ft_or,
	ft_xor,
	ft_zjmp,
	ft_ldi,
	ft_sti,
	ft_fork,
	ft_ld,
	ft_ldi,
	ft_lfork,
	ft_aff
};

void		process_play(t_listp *players, t_env *vm)
{
	t_process		*player;
	int				opcode;
	unsigned char	*memory;

	memory = vm->memory;
	while (players)
	{
		player = &players->process;
		if (player->active == false && player->state != dead)
		{
			if ((opcode = memory[player->pc] - 1) < NB_INSTR && opcode >= 0)
				player->callback = g_instr[opcode](vm, player);
			else
				player->pc = (player->pc == MEM_SIZE - 1) ? 0 : player->pc + 1;
		}
		else if (player->state != dead)
		{
			if (!(--player->delay))
			{
				player->callback(vm, player);
				player->active = false;
			}
		}
		players = players->next;
	}
}
