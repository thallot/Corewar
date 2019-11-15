/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 16:18:03 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/07 16:30:18 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		dump_memory(unsigned char memory[])
{
	int		i;

	i = 0;
	while (i < MEM_SIZE)
		ft_printf("|%02x", memory[i++]);
	ft_putchar('\n');
}