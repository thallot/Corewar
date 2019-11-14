/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/07 15:17:09 by jjaegle           #+#    #+#             */
/*   Updated: 2019/04/12 11:08:37 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*list_new;
	t_list	*list_next;
	t_list	*list_start;

	if (!lst)
		return (NULL);
	list_new = f(lst);
	list_start = list_new;
	while ((lst = lst->next))
	{
		list_next = f(lst);
		list_new->next = list_next;
		list_new = list_next;
	}
	list_new->next = NULL;
	return (list_start);
}
