/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 09:41:43 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/22 17:37:42 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "vm.h"

static int	is_champ(char *file)
{
	int		len;

	len = ft_strlen(file) - 1;
	if (file[len] == 'r' && file[len - 1] == 'o' && file[len - 2] == 'c'
		&& file[len - 3] == '.')
		return (1);
	return (0);
}

/*
**get_next_args lit l'argument s'ils s'agit dune option le type est retourne et
**av pointe maintenant sur la valeure de l'option qui sera interprete par
**pars_arg'
*/

static int	get_next_args(char **av[], t_env *vm)
{
	if (!ft_strcmp(**av, "-dump"))
	{
		(*av)++;
		return (DUMP);
	}
	else if (!ft_strcmp(**av, "-n"))
	{
		(*av)++;
		return (NUMBER);
	}
	else if (!ft_strcmp(**av, "-v"))
	{
		vm->visu = 1;
		return (VISUAL);
	}
	else if (is_champ(**av))
		return (CHAMP);
	else
		return (EXIT_FAILURE);
}

/*
**pars_arg appelle get_next arg pour recuperer le type de l'argument lu et le
**gere en foncion, si une erreure et reperer dans la structure d'un argument
**un code d'erreur sera envoyer au main pour etre traite.
**3 types d'arguments possibles : dump, number, champion.
*/

static int	pars_args(char **av[], t_env *env)
{
	int		ret;

	while (*(*av)++ && **av && (ret = get_next_args(av, env)))
	{
		if (ret == DUMP)
		{
			if (env->dump == UNDEF && ft_str_is(**av, ft_isdigit)
				&& ft_strcmp(**av, "0"))
				env->dump = ft_atoi(**av);
			else
				return (DUMP);
		}
		else if (ret == NUMBER)
		{
			if (ft_str_is(**av, ft_isdigit) && !in_array(**av, &env->tab_champ))
				add_champ_num(ft_atoi(**av), &env->tab_champ);
			else
				return (NUMBER);
		}
		else if (ret == CHAMP && (ret = add_champ(**av, &env->tab_champ)))
			return (ret);
		else if (ret == EXIT_FAILURE)
			return (ret);
	}
	return (EXIT_SUCCESS);
}

static void	initialise_env(t_env *env)
{
	int		i;

	ft_bzero(env, sizeof(*env));
	env->lastlive = UNDEF;
	env->dump = UNDEF;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		env->tab_champ.champs[i].num = UNINIT;
		env->nb_live[i] = 0;
		i++;
	}
}

int			main(int ac, char *av[])
{
	t_env		env;
	int			err;

	initialise_env(&env);
	if ((err = pars_args(&av, &env)))
		return (print_error(err, av));
	adjust_num(&env.tab_champ);
	if (env.tab_champ.nb_champ > 0)
	{
		if (create_process(&env))
			write(2, "Malloc error\n", 13);
		else
			lets_play(&env);
	}
	else
		write(2, "Champ needed\n", 13);
	(void)ac;
	return (clean_process(env.player));
}
