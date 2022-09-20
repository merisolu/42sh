/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jumanner <jumanner@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/22 11:36:17 by jumanner          #+#    #+#             */
/*   Updated: 2021/12/02 13:56:50 by jumanner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	handle_eof_or_error(int read_count, char **line)
{
	if (read_count == 0 && *line[0] != '\0')
		read_count = 1;
	else if (read_count <= 0)
		ft_memdel((void **)line);
	return (read_count);
}

static char	*transfer_buffer_to_line(char **line, char *buffer)
{
	char	*temp;
	char	*sub;
	char	*start;
	size_t	end;

	start = ft_memichr(buffer, '\0', GNL_BUFF_SIZE);
	end = 0;
	while (end < GNL_BUFF_SIZE && start[end] != '\n' && start[end] != '\0')
		end++;
	sub = ft_strsub(start, 0, end + 1);
	temp = *line;
	*line = ft_strjoin(temp, sub);
	ft_bzero(start, end + 1);
	free(temp);
	free(sub);
	return (*line);
}

int	ft_get_next_line(const int fd, char **line)
{
	static char	buffers[12289][GNL_BUFF_SIZE];
	int			read_count;

	if (fd < 0 || fd > 12288 || !line || GNL_BUFF_SIZE <= 0)
		return (-1);
	read_count = 1;
	*line = ft_strnew(0);
	if (!*line)
		return (-1);
	while (!ft_strchr(*line, '\n'))
	{
		if (!ft_memichr(buffers[fd], '\0', GNL_BUFF_SIZE))
			read_count = read(fd, buffers[fd], GNL_BUFF_SIZE);
		if (read_count <= 0)
			return (handle_eof_or_error(read_count, line));
		if (!transfer_buffer_to_line(line, buffers[fd]))
			return (-1);
	}
	ft_bzero(ft_strchr(*line, '\n'), 1);
	return (1);
}
