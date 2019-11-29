/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:52:01 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/29 11:20:53 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int			val_record(t_process *process, int registre, int opt)
{
	int		ret;

	ret = *(int*)process->records[registre - 1];
	if (opt == WRITE)
		ft_memrev(&ret, REG_SIZE);
	return (ret);
}

/*
**permet de retourner le type du prochain parametre a aller recuperer, si le
**masque ne correspond pas, retourne une valeure UNDEFINED qui marquera la fin
**de l'instruction en cours
*/

int			get_type(char encoded, int param)
{
	unsigned char	ret;

	ret = 0;
	if (param == FIRST)
		ret = (encoded >> 6) & 0x03;
	else if (param == SECND)
		ret = ((encoded << 2) >> 6) & 0x03;
	else if (param == THIRD)
		ret = ((encoded << 4) >> 6) & 0x03;
	if (ret == REG_CODE)
		return (REG_CODE);
	else if (ret == DIR_CODE)
		return (DIR_CODE);
	else if (ret == IND_CODE)
		return (IND_CODE);
	return (UNDEF);
}

/*
**get_params recupere tout les parametres d'une instruction
*/

int			get_params(t_process *process, unsigned char *memory
		, int nb, int d2)
{
	int				i;
	int				type;
	unsigned char	encoded;

	i = 0;
	encoded = get_encoded(process, memory);
	type = get_type(encoded, FIRST);
	while (i < nb)
	{
		process->param[i].ptr = get_param(process, memory, type, d2);
		if (!(process->param[i].ptr))
			return (EXIT_FAILURE);
		process->param[i].value = change_endian(process->param[i].ptr
				, get_size(type, d2));
		process->param[i].type = type;
		i++;
		if (i == 1)
			type = get_type(encoded, SECND);
		else if (i == 2)
			type = get_type(encoded, THIRD);
	}
	return (EXIT_SUCCESS);
}

/*
**get_param d'interface entre l'instruction et la memoire, modifie le pc d'un
**processeur et retourne les size octets demande
*/

char		*get_param(t_process *process, unsigned char memory[], int type
		, int d2)
{
	char	*ret;
	int		value;
	int		size;

	if (!(size = get_size(type, d2)))
		return (NULL);
	ret = (char*)&memory[process->pc];
	value = change_endian(ret, size);
	if (size == T_REG)
		if (value < 1 || value > 16)
			return (NULL);
	process->pc += size;
	return (ret);
}

int			get_adress(int start, int ind, int l)
{
	int		ret;
	int		sign;

	sign = 0;
	if (ind < 0)
	{
		sign = 1;
		ind = -ind;
	}
	ret = start;
	if (l == false)
		ind %= IDX_MOD;
	if (sign)
		ind = -ind;
	ret += ind;
	if (ret < 0)
	{
		ret %= MEM_SIZE;
		ret = MEM_SIZE + ret;
	}
	else
		ret %= MEM_SIZE;
	return (ret);
}
