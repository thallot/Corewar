/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <jjaegle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/18 15:54:06 by jjaegle           #+#    #+#             */
/*   Updated: 2019/09/17 17:32:29 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstcpy(t_list *src)
{
	t_list	*dest;
	t_list	*lst;

	dest = NULL;
	while (src)
	{
		if (!(lst = ft_lstnew(src->content, src->content_size)))
			exit(EXIT_FAILURE);
		ft_lstpush(&dest, lst);
		src = src->next;
	}
	return (dest);
}
