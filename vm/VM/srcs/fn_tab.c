/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_tab.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 11:55:27 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/22 17:50:57 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

/*
**Structure du tableau de champion :
**	-nb_champ : nombre de champion deja enregistrer dans la vm
**	-champs[] : tableau de champion
**		Le numero, le nom, le bloc d'instruction des champions sont dabbord
**		enregistre dans l'environnement de la Vm avant la creation de leur
**		processeur et l'insertion de leurs instructions en memoire.
*/

/*
**Verifie si le numero a deja ete attribue.
*/

int				in_array(char *str, t_tabchamp *tab)
{
	int		i;
	int		num;

	i = 0;
	num = ft_atoi(str);
	if (num > 0)
	{
		while (i <= tab->nb_champ)
		{
			if (tab->champs[i].num == num)
				return (1);
			i++;
		}
	}
	return (0);
}

int				in_arraynb(int num, t_tabchamp *tab)
{
	int		i;

	i = 0;
	if (num >= 0)
	{
		while (i <= tab->nb_champ)
		{
			if (tab->champs[i].num == num)
				return (i);
			i++;
		}
	}
	return (UNDEF);
}

/*
**Attribue des numeros, en partant de 1,  aux champion n'en ayant pas.
*/

void			adjust_num(t_tabchamp *tab)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < tab->nb_champ)
	{
		if (tab->champs[i].num == UNDEF)
		{
			while (in_arraynb(j, tab) != UNDEF)
				j++;
			tab->champs[i].num = j++;
		}
		i++;
	}
}

/*
**ajoute le nom et le bloc d'instruction du champion passe en parametre a
**l'environement de la VM en gerant les erreurs de tailles en octet et de
**quantite de champion (<= MAX_PLAYERS)
*/

int				add_champ(char *file, t_tabchamp *tab)
{
	int		i;
	int		ret;

	if (!is_filechamp(file))
		return (CHAMP);
	else if (tab->nb_champ == MAX_PLAYERS)
		return (MAX);
	i = tab->nb_champ;
	if (tab->champs[i].num == UNINIT)
		tab->champs[i].num = UNDEF;
	if ((ret = extract_info(file, &tab->champs[i])))
		return (ret);
	tab->nb_champ++;
	return (EXIT_SUCCESS);
}

void			add_champ_num(int num, t_tabchamp *tab)
{
	int		i;

	i = tab->nb_champ;
	tab->champs[i].num = num;
}
