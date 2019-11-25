/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 17:58:09 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/11 18:04:58 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstrev(t_list **al)
{
	t_list	*start;
	t_list	*ptr;
	t_list	*i;

	start = *al;
	if (*al)
	{
		while ((*al)->next)
			*al = (*al)->next;
		i = *al;
		while (i != start)
		{
			ptr = start;
			while (ptr->next != i)
				ptr = ptr->next;
			i->next = ptr;
			i = ptr;
		}
		i->next = NULL;
	}
}
