/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstshift.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/04 12:26:48 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/04 14:44:43 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstshift(t_list **al)
{
	t_list	*first;

	if (*al)
	{
		first = *al;
		*al = first->next;
		first->next = NULL;
		return (first);
	}
	return (NULL);
}
