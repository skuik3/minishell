/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anezkahavrankova <anezkahavrankova@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/24 22:49:08 by ehasalu           #+#    #+#             */
/*   Updated: 2025/08/10 16:44:53 by anezkahavra      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*trim(char *line)
{
	size_t	l;
	size_t	i;
	char	*trimmed;

	i = 0;
	l = 0;
	while ((line)[i] != '\n' && (line)[i])
		i++;
	if ((line)[i] == '\n')
		i++;
	if (gnl_ft_strlen(line) - i == 0)
	{
		//free(line);
		return (NULL);
	}
	trimmed = (char *)gnl_ft_calloc((gnl_ft_strlen(line) - i + 1), sizeof(char));
	if (!trimmed)
		return (NULL);
	while ((line)[i])
		trimmed[l++] = (line)[i++];
	trimmed[l] = '\0';
	//free(line);
	return (trimmed);
}

char	*cut_extra(char *line)
{
	char	*ret;
	size_t	i;
	size_t	l;

	l = 0;
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	ret = (char *)gnl_ft_calloc(sizeof(char), (i + 1));
	while (l < i)
	{
		ret[l] = line[l];
		l++;
	}
	ret[l] = '\0';
//	free(line);
	return (ret);
}

void	extra_fnc(int bytes, char **temp, char **line, char **buffer)
{
	(*temp)[bytes] = '\0';
	*line = gnl_ft_strjoin(*line, *temp);
	if (buffer != NULL)
	{
		//free(*buffer);
		*buffer = gnl_ft_strdup("");
	}
	*buffer = gnl_ft_strjoin(*buffer, *temp);
}

char	*read_fd(char **buffer, int fd)
{
	int		bytes;
	char	*line;
	char	*temp;

	line = gnl_ft_strdup("");
	line = gnl_ft_strjoin(line, *buffer);
	temp = (char *)gnl_ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	while (gnl_ft_strchr(*buffer, '\n') == NULL)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes <= 0)
		{
			// free(temp);
			if (gnl_ft_strlen(line) != 0)
				return (cut_extra(line));
			// free (line);
			return (NULL);
		}
		extra_fnc(bytes, &temp, &line, buffer);
	}
	//free(temp);
	return (cut_extra(line));
}

char	*get_next_line(int fd)
{
	static char	*buf[2048];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > 256)
		return (NULL);
	if (!buf[fd])
		buf[fd] = (char *)gnl_ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	line = read_fd(&buf[fd], fd);
	buf[fd] = trim(buf[fd]);
	return (line);
}
