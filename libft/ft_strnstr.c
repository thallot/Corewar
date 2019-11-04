/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:32:43 by thallot           #+#    #+#             */
/*   Updated: 2019/04/03 14:24:22 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*str;
	char	*find;
	size_t	i;
	int		j;

	i = 0;
	str = (char *)haystack;
	find = (char *)needle;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (i < len && str[i] != '\0')
	{
		j = 0;
		if (str[i] == find[j])
		{
			while (str[i + j] == find[j])
			{
				if (find[j + 1] == '\0' && i + j < len)
					return (&str[i]);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
