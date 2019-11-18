/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 15:52:01 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/14 15:35:04 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		val_record(t_process *process, int registre,int opt)
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

int			get_size(char encoded, int param, enum e_bool d2)
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
		return (T_REG);
	else if (ret == DIR_CODE)
	{
		if (d2 == false)
			return (DIR_SIZE);
		return (DIR_SIZE);
	}
	else if (ret == IND_CODE)
		return (IND_SIZE);
	return (UNDEF);
}

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

int		get_params(t_process *process, unsigned char *memory
		, int nb, enum e_bool d2)
{
	int		i;
	int		size;
	int type;
	unsigned char encoded;

	i = 0;
	encoded = get_encoded(process, memory);
	size = get_size(encoded, FIRST, d2);
	type = get_type(encoded, FIRST);
	while (i < nb)
	{
		process->param[i].ptr = get_param(process, memory,  size);
		process->param[i].size = size;
		process->param[i].value = change_endian(process->param[i].ptr, size);
		process->param[i].type = type;
	//	ft_printf("GPs : value %d = %d\n", i, process->param[i].value);
		if (!(process->param[i].ptr))
			return (EXIT_FAILURE);
		i++;
		if (i == 1)
		{
			size = get_size(encoded, SECND, d2);
			type = get_type(encoded, SECND);
		}
		else if (i == 2)
		{
			size = get_size(encoded, THIRD, d2);
			type = get_type(encoded, THIRD);
		}

	}
	printf("success\n");
	return (EXIT_SUCCESS);
}

/*
**get_param d'interface entre l'instruction et la memoire, modifie le pc d'un
**processeur et retourne les size octets demande
*/

char		*get_param(t_process *process, unsigned char memory[], size_t size)
{
	char	*ret;
	int		value;

	if ((int)size == UNDEF)
		return (NULL);
	ret = (char*)&memory[process->pc];
	value = change_endian(ret, size);
	if (size == T_REG)
		if (value < 1 || value > 16)
			return (NULL);
	process->pc += size;
	return (ret);
}

int		get_adress(int start, int ind, enum e_bool l)
{
	int		ret;

	ret = start;
	if (l == false)
		ind %= IDX_MOD;
	ret += ind;
	ret %= MEM_SIZE;
	return (ret);
}
