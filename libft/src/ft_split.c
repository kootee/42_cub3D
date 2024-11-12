/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:37:01 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:36 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_count_strs(const char *s, char c)
{
	int	i;
	int	str_num;
	int	str_len;

	i = 0;
	str_num = 0;
	str_len = ft_strlen(s);
	while (s[i])
	{
		while (i < str_len && s[i] == c)
			i++;
		while (i < str_len && s[i] != c)
			i++;
		if (i == str_len && s[str_len - 1] == c)
			return (str_num);
		str_num++;
	}
	return (str_num);
}

static void	ft_free(char **ptr, int ptr_index)
{
	int	i;

	i = 0;
	while (i <= ptr_index)
	{
		free(ptr[i]);
		i++;
	}
	free(ptr);
}

static int	ft_set_strs(char const *s, char **ptr, int num_of_strs, char c)
{
	unsigned int	i;
	unsigned int	j;
	int				ptr_index;

	i = 0;
	j = 0;
	ptr_index = 0;
	while (ptr_index < num_of_strs && i + j < ft_strlen(s))
	{
		while (i < ft_strlen(s) && s[i] == c)
			i++;
		while ((i + j) < ft_strlen(s) && s[i + j] != c)
			j++;
		ptr[ptr_index] = ft_substr(s, i, j);
		if (!ptr[ptr_index])
		{
			ft_free(ptr, ptr_index);
			return (1);
		}
		i += j;
		j = 0;
		ptr_index++;
	}
	ptr[num_of_strs] = 0;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**splt_ptr;
	int		num_of_strs;

	if (!s)
		return (0);
	num_of_strs = ft_count_strs(s, c);
	splt_ptr = malloc((num_of_strs + 1) * sizeof(char *));
	if (!splt_ptr)
		return (0);
	if (ft_set_strs(s, splt_ptr, num_of_strs, c))
		return (0);
	return (splt_ptr);
}
