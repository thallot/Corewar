/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fn_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjaegle <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/06 13:28:45 by jjaegle           #+#    #+#             */
/*   Updated: 2019/11/22 17:49:39 by jjaegle          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "op.h"

static int	has_magic(char *str, int len)
{
	int				i;
	unsigned int	mask;
	unsigned int	ret;

	i = 0;
	ret = 0;
	while (i < len)
	{
		mask = 0;
		mask = str[i];
		mask <<= (32 - 8);
		mask >>= (8 * i);
		ret |= mask;
		i++;
	}
	return (ret == COREWAR_EXEC_MAGIC ? 1 : 0);
}

int			too_big(int fd)
{
	close(fd);
	return (BIG);
}

int			extract_info(char *file, t_info_champ *champ)
{
	int		fd;
	char	buf[CHAMP_MAX_SIZE + 2];
	int		ret;

	fd = open(file, O_RDONLY);
	if (fd > -1)
	{
		lseek(fd, 136, SEEK_SET);
		ret = read(fd, buf, 4);
		buf[ret] = '\0';
		if ((champ->size = change_endian((void *)&buf, 4)) > CHAMP_MAX_SIZE)
			return (too_big(fd));
		lseek(fd, 4, SEEK_SET);
		ret = read(fd, buf, PROG_NAME_LENGTH);
		buf[ret] = '\0';
		ft_strcpy(champ->name, buf);
		lseek(fd, 2192, SEEK_SET);
		ret = read(fd, buf, CHAMP_MAX_SIZE + 1);
		buf[ret] = '\0';
		ft_memcpy(champ->instr, buf, ret);
	}
	close(fd);
	return (EXIT_SUCCESS);
}

int			is_filechamp(char *file)
{
	int		fd;
	char	buf[5];
	int		ret;

	if ((fd = open(file, O_RDONLY)) == -1)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	if ((ret = read(fd, buf, 4)) == -1)
	{
		perror("read");
		exit(EXIT_FAILURE);
	}
	buf[ret] = '\0';
	ret = has_magic(buf, 4);
	close(fd);
	return (ret);
}
