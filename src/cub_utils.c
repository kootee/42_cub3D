/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:53:08 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/18 16:30:18 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_texture_coordinate(char *str)
{
	return (strncmp(str, "NO ", 3) == 0
		|| strncmp(str, "SO ", 3) == 0
		||strncmp(str, "WE ", 3) == 0
		|| strncmp(str, "EA ", 3) == 0);
}

void	check_texture(char *path, t_cub *cub)
{
	if (!path)
		error_terminate_mlx(cub, ERROR_MALLOC_FAIL);
}

void	skip_rgb_whitespace(char **strs)
{
	char	*trimmed_str;
	int		i;
	int		j;
	
	i = 0;
	while (strs[i])
	{
		j = 0;
		while(strs[i][j] == ' ' || strs[i][j] == '\t' || strs[i][j] == '\r')
			j++;
		trimmed_str = ft_strdup(strs[i] + j);
		free(strs[i]);
		strs[i] = trimmed_str;
		i++;
	}
}

char *skip_whitespace(char *str)
{
	char *trimmed_str;
	int i;

	i = 0;
	while(str[i] == ' ' || str[i] == '\t' || str[i] == '\r')
		i++;
	trimmed_str = ft_strdup(str + i);
	free(str);
	return(trimmed_str);
}

int	is_valid_map_line(t_cub *cub, char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\r')
		line++;
	if (*line == '1' && cub->textures.north_path != NULL \
	&& cub->textures.south_path != NULL \
	&& cub->textures.east_path != NULL \
	&& cub->textures.west_path != NULL
	&& cub->colors_set == 2)
	{
		return (1);
	}
	else
		return (0);
}
