/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/03 13:09:16 by thallot           #+#    #+#             */
/*   Updated: 2019/04/03 13:30:22 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

char	*ft_strstr(const char *haystack, const char *needle)
{
	char	*str;
	char	*find;
	int		i;
	int		j;

	i = 0;
	str = (char *)haystack;
	find = (char *)needle;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (str[i] != '\0')
	{
		j = 0;
		if (str[i] == find[j])
		{
			while (str[i + j] == find[j])
			{
				if (find[j + 1] == '\0')
					return (str + i);
				j++;
			}
		}
		i++;
	}
	return (NULL);
}
