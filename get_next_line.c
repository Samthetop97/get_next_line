/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadir <shadir@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:11:01 by shadir            #+#    #+#             */
/*   Updated: 2023/11/03 18:58:47 by shadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_rid_of_line(char *buf)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	j = i;
	while (buf[j] != '\0')
		j++;
	tmp = (char *)malloc(sizeof(char) * (j - 1));
	if (!tmp)
		return (NULL);
	i++;
	j = 0;
	while (buf[i])
		tmp[j++] = buf[i++];
	tmp[j] = '\0';
	free(buf);
	return (tmp);
}

char	*ft_get_line(char *buf)
{
	int		i;
	char	*line;

	i = 0;
	if (!buf[i])
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] && buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_buffer(char *buf, int fd)
{
	char	*str;
	ssize_t	rd;

	str = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	rd = 1;
	while (!ft_strchr(buf, '\n') && rd != 0)
	{
		rd = read(fd, str, BUFFER_SIZE);
		if (rd == -1)
		{
			free(str);
			free(buf);
			return (NULL);
		}
		str[rd] = '\0';
		buf = ft_strjoin(buf, str);
	}
	free(str);
	return (buf);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = get_buffer(buf, fd);
	if (!buf)
		return (NULL);
	line = ft_get_line(buf);
	buf = get_rid_of_line(buf);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("file.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
