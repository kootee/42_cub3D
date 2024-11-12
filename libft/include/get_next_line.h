/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 16:09:09 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/05 10:21:36 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct s_gnl_lst
{
	char				*string;
	struct s_gnl_lst	*next;
}				t_gnl_lst;

char		*get_next_line(int fd);
char		*clear_list(t_gnl_lst **list, t_gnl_lst *new_node, char *buffer);
void		add_clean_node(t_gnl_lst *last_n, t_gnl_lst *clean_n, char *buff);
int			ft_lstadd_node(t_gnl_lst **lst, char *buf);
int			found_newline(t_gnl_lst *node);
t_gnl_lst	*ft_lstlast_gnl(t_gnl_lst *lst);

#endif