/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <jjaegle@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/07 12:01:39 by jjaegle           #+#    #+#             */
/*   Updated: 2019/10/09 12:24:11 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static t_list	*find_mail(t_list **first, const int fd)
{
	t_list			*elem;

	elem = *first;
	while (elem)
	{
		if ((*elem).content_size == (size_t)fd)
			return (elem);
		elem = elem->next;
	}
	elem = ft_lstnew(NULL, fd);
	(*elem).content_size = fd;
	ft_lstadd(first, elem);
	return (elem);
}

static void		remove_mail(t_list *mail)
{
	(*mail).content = my_free((*mail).content);
	free(mail);
}

static void		ft_lstremoveif(t_list **first, const int fd)
{
	t_list			*cur;
	t_list			*prev;

	cur = *first;
	if ((*cur).content_size == (size_t)fd)
	{
		*first = cur->next;
		remove_mail(cur);
		return ;
	}
	prev = cur;
	cur = cur->next;
	while (cur)
	{
		if ((*cur).content_size == (size_t)fd)
		{
			prev->next = cur->next;
			remove_mail(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
}

static void		line_and_new(char **line, char **s)
{
	char			*str;

	if (ft_strstr(*s, "\n") != NULL)
	{
		*line = ft_strsub(*s, 0, ft_strstr(*s, "\n") - *s);
		str = ft_strdup(ft_strstr(*s, "\n") + 1);
		*s = my_free(*s);
		*s = str;
		if (!*line)
			*line = ft_strdup("\0");
	}
	else if (*s && **s != '\0')
	{
		*line = ft_strdup(*s);
		*s = my_free(*s);
	}
}

int				get_next_line(const int fd, char **line, int opt)
{
	static t_list	*first = NULL;
	t_list			*mail;
	char			buf[BUFF_SIZ + 1];
	int				ret;

	if (!opt)
	{
		if (!line || read(fd, buf, 0) < 0)
			return (-1);
		*line = my_free(*line);
		mail = find_mail(&first, fd);
		while (!ft_strchr(mail->content, '\n')
				&& (ret = read(fd, buf, BUFF_SIZ)) > 0)
		{
			buf[ret] = '\0';
			mail->content = ft_joinfree(mail->content, buf);
		}
		line_and_new(line, (char**)&mail->content);
		if (*line)
			return (1);
	}
	ft_lstremoveif(&first, fd);
	return (0);
}
