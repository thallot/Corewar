/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstremoveone.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 15:40:56 by jjaegle           #+#    #+#             */
/*   Updated: 2019/07/18 16:16:40 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstremoveone(t_list *previous, t_list **to_del)
{
	previous->next = (*to_del)->next;
	free((*to_del)->content);
	(*to_del)->content = NULL;
	free(*to_del);
	*to_del = NULL;
}
