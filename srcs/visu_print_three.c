/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visu_print_three.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 14:19:38 by thallot           #+#    #+#             */
/*   Updated: 2019/11/28 15:45:21 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

void	print_aff(t_visu *visu, WINDOW *info)
{
	if (visu->vm->aff)
		mvwprintw(info, 58, 3, "Aff : %c", visu->vm->aff);
}
