/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thallot <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 18:12:27 by edillenb          #+#    #+#             */
/*   Updated: 2019/10/16 12:15:23 by thallot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#define OP OPEN_MAX

static int		del_str_int(char **str)
{
	ft_memdel((void**)str);
	return (-1);
}

static char		*del_str(char **str)
{
	ft_memdel((void**)str);
	return (NULL);
}

static int		m_stor(char **stor)
{
	if (!*stor)
	{
		if (!(*stor = (char*)malloc(sizeof(char) * 1)))
			return (-1);
		(*stor)[0] = '\0';
	}
	return (0);
}

static char		*trim_to_eol(char **str)
{
	char	*result;
	char	*new_str;
	int		len;
	int		i;

	len = 0;
	new_str = NULL;
	while ((*str)[len] != '\n' && (*str)[len])
		len++;
	if (len != 0 && (*str)[len] == '\0')
		return (del_str(str));
	i = ft_strlen(*str) - len;
	if (!(result = ft_strsub((const char**)str, 0, len, 0)))
		return (del_str(str));
	if (!(new_str = ft_strsub((const char**)str, len + 1, i, 0)))
	{
		ft_memdel((void**)str);
		ft_memdel((void**)result);
		return (NULL);
	}
	ft_strdel(str);
	*str = new_str;
	return (result);
}

int				get_next_line(const int fd, char **line, int opt, int ret)
{
	char			buf[BUFF_SIZE + 1];
	static char		*stor = NULL;
	char			*temp;

	temp = NULL;
	if (opt == 0)
		return (del_str_int(&stor));
	if (!line || fd < 0 || fd > OP || BUFF_SIZE < 1 || m_stor(&stor) == -1)
		return (-1);
	while (!(ft_strchr(stor, '\n')) && (ret = read(fd, buf, BUFF_SIZE)))
	{
		buf[ret] = '\0';
		if (ret == -1 || !(temp = ft_strjoin(stor, buf)) || temp[0] == '\0')
			return (del_str_int(&stor));
		ft_memdel((void**)&stor);
		stor = temp;
	}
	if (ret == 0 && ft_strlen(stor) == 0)
		return (0);
	if (!(*line = trim_to_eol(&stor)))
		return (-1);
	if (ret == 0 && ft_strlen(stor) == 0)
		ft_memdel((void**)&stor);
	return (1);
}
