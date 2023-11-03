/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shadir <shadir@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 14:11:01 by shadir            #+#    #+#             */
/*   Updated: 2023/11/02 23:50:30 by shadir           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_rid_of_line(char *buf)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (buf[i] != '\n')
		i++;
	j = i;
	while (buf[j] != '\0')
		j++;
	if (!buf)
		return (NULL);
	tmp = (char *)malloc(sizeof(char) * (j - i) + 1);
	if (!tmp)
		return (NULL);
	j = 0;
	while (buf[i++] != '\0')
	{
		tmp[j] = buf[i];
		j++;
	}
	tmp[j] = '\0';
	free(buf);
	return (tmp);
}

char	*get_line(char *buf)
{
	int		i;
	char	*line;

	line = NULL;
	i = 0;
	while (buf[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * i + 2);
	if (!line)
		return (NULL);
	i = 0;
	while (buf[i] != '\n')
	{
		line[i] = buf[i];
		i++;
	}
	line[i] = '\n';
	line[i + 1] = '\0';
	return (line);
}

char	*get_buffer(int fd, char *buf)
{
	char	*str;
	ssize_t	rd;

	str = NULL;
	str = calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!str)
		return (NULL);
	rd = 1;
	while (rd > 0)
	{
		rd = read(fd, str, BUFFER_SIZE);
		if (rd < 0)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		str[rd] = '\0';
		buf = ft_strjoin(buf, str);
		if (ft_strrchr(buf, '\n') || ft_strrchr(buf, '\0'))
			break ; // Stop reading if a newline or null terminator is found
	}
	free(str);
	return (buf);
}

// char	*get_buffer(int fd, char *buf)
// {
// 	char	*str;
// 	size_t	rd;

// 	str = NULL;
// 	str = calloc(BUFFER_SIZE + 1, sizeof(char));
// 	if (!str)
// 		return (NULL);
// 	rd = 1;
// 	while (!ft_strrchr(str, '\n') || !ft_strrchr(str, '\0'))
// 	{
// 		rd = read(fd, str, BUFFER_SIZE);
// 		if (rd <= 0)
// 		{
// 			free(buf);
// 			free(str);
// 			return (NULL);
// 		}
// 		str[rd] = '\0';
// 		buf = ft_strjoin(buf, str);
// 	}
// 	free(str);
// 	return (buf);
// }

char	*get_next_line(int fd)
{
	static char	*buf;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = get_buffer(fd, buf);
	if (!buf)
	{
		free(buf);
		return (NULL);
	}
	line = get_line(buf);
	buf = get_rid_of_line(buf);
	return (line);
}

int	main(void)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open("test.txt", O_RDONLY);
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	return (0);
}
