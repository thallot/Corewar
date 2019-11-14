/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/09 14:23:54 by thallot           #+#    #+#             */
/*   Updated: 2019/04/19 17:30:39 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *new_lst;

	if (!lst || !f)
		return (NULL);
	if (!(new_lst = ft_lstnew(f(lst)->content, f(lst)->content_size)))
		return (NULL);
	new_lst->next = ft_lstmap(lst->next, f);
	return (new_lst);
}
