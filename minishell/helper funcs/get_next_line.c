/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: skuik <skuik@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:22:28 by skuik             #+#    #+#             */
/*   Updated: 2025/02/11 15:09:01 by skuik            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	polish_list(t_list_gnl **list_gnl)
{
	t_list_gnl	*last_node;
	t_list_gnl	*clean_node;
	int			i;
	int			k;
	char		*buf;

	buf = malloc(BUFFER_SIZE + 1);
	clean_node = malloc(sizeof(t_list_gnl));
	if (NULL == buf || NULL == clean_node)
		return ;
	last_node = f_last_node(*list_gnl);
	i = 0;
	k = 0;
	while (last_node->str_buf_g[i] && last_node->str_buf_g[i] != '\n')
		++i;
	while (last_node->str_buf_g[i] && last_node->str_buf_g[++i])
		buf[k++] = last_node->str_buf_g[i];
	buf[k] = '\0';
	clean_node->str_buf_g = buf;
	clean_node->next_gnl = NULL;
	dealloc(list_gnl, clean_node, buf);
}

char	*get_line(t_list_gnl *list_gnl)
{
	int		str_len;
	char	*next_str;

	if (NULL == list_gnl)
		return (NULL);
	str_len = len_to_nline(list_gnl);
	next_str = malloc(str_len + 1);
	if (NULL == next_str)
		return (NULL);
	copy_str(list_gnl, next_str);
	return (next_str);
}

void	append(t_list_gnl **list_gnl, char *buf)
{
	t_list_gnl	*new_node;
	t_list_gnl	*last_node;

	last_node = f_last_node(*list_gnl);
	new_node = malloc(sizeof(t_list_gnl));
	if (NULL == new_node)
		return ;
	if (NULL == last_node)
		*list_gnl = new_node;
	else
		last_node->next_gnl = new_node;
	new_node->str_buf_g = buf;
	new_node->next_gnl = NULL;
}

void	make_list(t_list_gnl **list_gnl, int fd)
{
	int		char_read;	
	char	*buf;

	while (!f_nline(*list_gnl))
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (NULL == buf)
			return ;
		char_read = read(fd, buf, BUFFER_SIZE);
		if (char_read <= 0)
		{
			free(buf);
			return ;
		}
		buf[char_read] = '\0';
		append(list_gnl, buf);
	}
}

char	*get_next_line(int fd)
{
	static t_list_gnl	*list = NULL;
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	make_list(&list, fd);
	if (list == NULL)
		return (NULL);
	next_line = get_line(list);
	polish_list(&list);
	return (next_line);
}

// int main()
// {
// 	int	fd;
// 	char	*line;
// 	int	lines;

// 	lines = 1;
// 	fd = open("lorem.txt", O_RDONLY);

// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%d->%s\n", lines++, line);
// 	}
// }
