/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:08:45 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:57:15 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h" 

char	*clear_list(t_gnl_lst **list, t_gnl_lst *new_node, char *buffer)
{
	t_gnl_lst	*temp;

	if (*list == NULL)
		return (NULL);
	while (*list)
	{
		temp = (*list)->next;
		free((*list)->string);
		free(*list);
		*list = temp;
	}
	*list = NULL;
	if (!new_node || *new_node->string)
		*list = new_node;
	else if (buffer != NULL && new_node != NULL)
	{
		free(buffer);
		free(new_node);
	}
	return (NULL);
}

void	add_clean_node(t_gnl_lst *last_node, t_gnl_lst *clean_node, char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (last_node->string[i] && last_node->string[i] != '\n')
		++i;
	while (last_node->string[i] && last_node->string[++i])
		buff[j++] = last_node->string[i];
	buff[j] = 0;
	clean_node->string = buff;
	clean_node->next = NULL;
}

int	ft_lstadd_node(t_gnl_lst **lst, char *buffer)
{
	t_gnl_lst	*last_node;
	t_gnl_lst	*new_node;

	if (!lst || !buffer)
		return (0);
	last_node = ft_lstlast_gnl(*lst);
	new_node = malloc(sizeof(t_gnl_lst));
	if (!new_node)
		return (0);
	new_node->string = buffer;
	new_node->next = NULL;
	if (!*lst)
		*lst = new_node;
	else
		last_node->next = new_node;
	return (1);
}

int	found_newline(t_gnl_lst *node)
{
	int		i;

	if (node == NULL)
		return (0);
	while (node)
	{
		i = 0;
		while (node->string[i])
		{
			if (node->string[i] == '\n')
				return (1);
			i++;
		}
		node = node->next;
	}
	return (0);
}

t_gnl_lst	*ft_lstlast_gnl(t_gnl_lst *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
