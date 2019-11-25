/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmergesort.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:30:43 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/11 19:11:00 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		insert(t_list *cell, t_list **al, int (*f)(void*, void*))
{
	t_list	*list;

	list = *al;
	if ((*f)(cell->content, list->content) < 1)
		ft_lstadd(al, cell);
	else
	{
		while (list->next)
		{
			if ((*f)(cell->content, list->next->content) < 1)
			{
				ft_lstinsert(list, cell);
				return ;
			}
			list = list->next;
		}
		list->next = cell;
	}
}

static t_list	*merge(t_list *l1, t_list *l2, int (*f)(void*, void*))
{
	t_list	*cell;

	if (!l2)
		return (l1);
	while ((cell = ft_lstshift(&l1)))
		insert(cell, &l2, (*f));
	return (l2);
}

t_list			*ft_lstmergesort(t_list *lst, int (*f)(void*, void*))
{
	t_list	*l1;
	t_list	*tmp;
	t_list	*l2;
	int		mid;

	if (!lst || !lst->next)
		return (lst);
	l1 = lst;
	tmp = l1;
	mid = ft_lstlen(lst) / 2;
	while (--mid)
		tmp = tmp->next;
	l2 = tmp->next;
	tmp->next = NULL;
	return (merge(ft_lstmergesort(l1, (*f)), ft_lstmergesort(l2, (*f)), (*f)));
}
