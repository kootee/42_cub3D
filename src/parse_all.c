/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:26:45 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/07 20:26:58 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_colors(char *line, uint32_t *color)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;

	rgb_values = ft_split(line + 2, ',');
	if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2])
	{
		free_array(rgb_values);
		handle_error(ERROR_INVALID_FILE_NAME);
	}
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_array(rgb_values);
		handle_error(ERROR_INVALID_FILE_NAME);
	}
	*color = (r << 16) | (g << 8) | b;
	free_array(rgb_values);
}

void	parse_textures(char *line, t_cub *cub)
{
	if (strncmp(line, "NO ", 3) == 0)
	{
		cub->textures.north_path = ft_strdup(line + 3);
		if (!cub->textures.north_path)
			handle_error(ERROR_MALLOC_FAIL);
	}
	else if (strncmp(line, "SO ", 3) == 0)
	{
		cub->textures.south_path = ft_strdup(line + 3);
		if (!cub->textures.south_path)
			handle_error(ERROR_MALLOC_FAIL);
	}
	else if (strncmp(line, "WE ", 3) == 0)
	{
		cub->textures.west_path = ft_strdup(line + 3);
		if (!cub->textures.west_path)
			handle_error(ERROR_MALLOC_FAIL);
	}
	else if (strncmp(line, "EA ", 3) == 0)
	{
		cub->textures.east_path = ft_strdup(line + 3);
		if (!cub->textures.east_path)
			handle_error(ERROR_MALLOC_FAIL);
	}
	else
	{
		handle_error(ERROR_INVALID_FILE_NAME);
	}
}

void	copy_map(char **lines, t_cub *cub)
{
	int	i;

	i = 0;
	while (lines[i])
		i++;
	cub->map_height = i;
	cub->map = malloc(sizeof(char *) * (i + 1));
	if (!cub->map)
	{
		fprintf(stderr, "Error\nFailed to allocate memory for map.\n");
		return ;
	}
	i = 0;
	while (lines[i])
	{
		cub->map[i] = ft_strdup(lines[i]);
		i++;
	}
	cub->map[i] = NULL;
}

int	parse_cub_file(t_cub *cub, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (strncmp(lines[i], "NO ", 3) == 0
			|| strncmp(lines[i], "SO ", 3) == 0
			||strncmp(lines[i], "WE ", 3) == 0
			|| strncmp(lines[i], "EA ", 3) == 0)
		{
			parse_textures(lines[i], cub);
		}
		else if (strncmp(lines[i], "F ", 2) == 0)
		{
			parse_colors(lines[i], &cub->floor_color);
		}
		else if (strncmp(lines[i], "C ", 2) == 0)
		{
			parse_colors(lines[i], &cub->ceiling_color);
		}
		else if (lines[i][0] == '1')
		{
			copy_map(&lines[i], cub);
			calculate_map_width(cub);
			if (is_map_valid(cub))
				return (1);
			break ;
		}
		else
		{
			handle_error(ERROR_INVALID_FILE_NAME);
		}
		i++;
	}
	return (0);
}
