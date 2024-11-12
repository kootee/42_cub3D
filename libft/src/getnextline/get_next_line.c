/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:12:14 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:57:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"

static void	copy_til_newline(char *new_line, t_gnl_lst *list_node)
{
	int	i;
	int	j;

	j = 0;
	if (list_node == NULL || list_node->string == NULL)
		return ;
	while (list_node)
	{
		i = 0;
		while (list_node->string[i])
		{
			if (list_node->string[i] == '\n')
			{
				new_line[j] = '\n';
				new_line[++j] = 0;
				return ;
			}
			new_line[j++] = list_node->string[i++];
		}
		list_node = list_node->next;
	}
	new_line[j] = 0;
}

static size_t	count_til_newline(t_gnl_lst *list_node)
{
	size_t	len;
	int		j;

	len = 0;
	while (list_node)
	{
		j = 0;
		while (list_node->string[j])
		{
			if (list_node->string[j] == '\n')
				return (++len);
			len++;
			j++;
		}
		list_node = list_node->next;
	}
	return (len);
}

static char	*prep_for_nextline(t_gnl_lst **list)
{
	t_gnl_lst	*clean_node;
	t_gnl_lst	*last_node;
	int			i;
	char		*buffer;

	i = 0;
	last_node = ft_lstlast_gnl(*list);
	clean_node = malloc(sizeof(t_gnl_lst));
	if (clean_node == NULL)
		return (clear_list(list, NULL, NULL));
	while (last_node->string[i])
		i++;
	buffer = malloc(i + 1);
	if (buffer == NULL)
	{
		free(clean_node);
		return (clear_list(list, NULL, NULL));
	}
	add_clean_node(last_node, clean_node, buffer);
	clear_list(list, clean_node, buffer);
	return (buffer);
}

static int	get_lines(t_gnl_lst **str_list, int fd)
{
	char	*buffer;
	int		bytes_read;

	while (!found_newline(*str_list))
	{
		buffer = malloc(BUFFER_SIZE + 1);
		if (!buffer)
			return (0);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
		{
			free(buffer);
			return (1);
		}
		buffer[bytes_read] = 0;
		if (!ft_lstadd_node(str_list, buffer))
		{
			free(buffer);
			return (0);
		}
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static t_gnl_lst	*str_list = NULL;
	char				*next_line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &next_line, 0) < 0)
		return (clear_list(&str_list, NULL, NULL));
	if (!get_lines(&str_list, fd))
		return (clear_list(&str_list, NULL, NULL));
	next_line = malloc(count_til_newline(str_list) + 1);
	if (next_line == NULL)
		return (clear_list(&str_list, NULL, NULL));
	copy_til_newline(next_line, str_list);
	if (next_line == NULL || str_list == NULL)
	{
		free(next_line);
		return (clear_list(&str_list, NULL, NULL));
	}
	if (!prep_for_nextline(&str_list))
	{
		free(next_line);
		return (NULL);
	}
	return (next_line);
}
