/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agara <agara@student.42vienna.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 21:54:29 by agara             #+#    #+#             */
/*   Updated: 2025/01/16 21:54:30 by agara            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_nl(char *buf)
{
	int	i;

	if (!buf)
		return (0);
	i = -1;
	while (buf[++i])
	{
		if (buf[i] == '\n')
			return (i + 1);
	}
	return (0);
}

static int	readloop(int fd, char **buf)
{
	int		readbytes;
	char	*temp;
	char	*chunk;

	while (1)
	{
		if (get_nl(*buf))
			return (1);
		chunk = ft_calloc(sizeof(char), BUFFER_SIZE + 1);
		if (!chunk)
			return (ft_terminate(1, buf), 0);
		readbytes = read(fd, chunk, BUFFER_SIZE);
		if (readbytes < 0)
			return (ft_terminate(2, &chunk, buf), 0);
		temp = ft_strjoin(*buf, chunk);
		ft_terminate(2, buf, &chunk);
		if (!temp)
			return (ft_terminate(2, &chunk, buf), 0);
		*buf = temp;
		if (readbytes < BUFFER_SIZE)
			return (1);
	}
}

static int	allocate(char **buf, char **line, char **newbuf)
{
	if (!get_nl(*buf))
	{
		*line = ft_strdup(*buf);
		if (!(*line))
			return (ft_terminate(1, buf), -1);
		return (ft_terminate(1, buf), 1);
	}
	else if (get_nl(*buf) == (int)ft_strlen(*buf))
	{
		*line = ft_strdup(*buf);
		if (!(*line))
			return (-1);
		return (ft_terminate(1, buf), 1);
	}
	else
	{
		*line = ft_calloc(sizeof(char), get_nl(*buf) + 1);
		if (!(*line))
			return (-1);
		*newbuf = ft_calloc(sizeof(char),
				(((int)ft_strlen(*buf) + 1) - get_nl(*buf)));
		if (!*newbuf)
			return (ft_terminate(2, buf, line), -1);
	}
	return (0);
}

static int	extract_leftover(char **buf, char **line)
{
	char	*newbuf;
	int		i;
	int		j;
	int		flag;

	flag = allocate(buf, line, &newbuf);
	if (flag == -1)
		return (0);
	if (flag == 1)
		return (1);
	i = 0;
	while ((*buf)[i] != '\n')
	{
		(*line)[i] = (*buf)[i];
		i++;
	}
	(*line)[i++] = '\n';
	j = 0;
	while ((*buf)[i])
		newbuf[j++] = (*buf)[i++];
	ft_terminate(1, buf);
	*buf = newbuf;
	return (1);
}

char	*get_next_line(int fd, int *flag)
{
	static char	*buf = NULL;
	char		*line;
	
	line = NULL;
	if (*flag == -1)
		return (ft_terminate(1, &buf), NULL);
	*flag = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!readloop(fd, &buf))
		return (ft_terminate(1, &buf), NULL);
	if (!extract_leftover(&buf, &line))
		return (ft_terminate(1, &buf), NULL);
	*flag = 1;
	return (line);
}
