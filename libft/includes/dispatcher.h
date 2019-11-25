/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 11:52:21 by jjaegle           #+#    #+#             */
/*   Updated: 2019/06/13 07:46:23 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DISPATCHER_H
# define DISPATCHER_H
# include "../includes/ft_printf.h"
# define OPT 13

t_opp	g_dispatcher[] =
{
	{'x', &ft_is_hexa},
	{'X', &ft_is_hexa},
	{'o', &ft_is_oct},
	{'d', &ft_is_int},
	{'i', &ft_is_int},
	{'c', &ft_is_char},
	{'u', &ft_is_uns},
	{'p', &ft_is_add},
	{'s', &ft_is_str},
	{'b', &ft_is_bin},
	{'f', &ft_is_float},
	{'e', &ft_is_exp},
	{'w', &ft_is_fd},
};

#endif
