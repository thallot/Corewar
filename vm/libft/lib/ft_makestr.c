/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_makestr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/09 13:46:17 by jjaegle           #+#    #+#             */
/*   Updated: 2019/05/09 13:47:50 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*make_str(size_t size, char c)
{
	char	*str;

	str = ft_strnew(size);
	ft_memset((void*)str, c, size);
	return (str);
}
