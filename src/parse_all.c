/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_all.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:26:45 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/18 17:16:37 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	check_colors(char **rgb_values, t_cub *cub)
{
	if (!rgb_values)
		error_terminate_mlx(cub, ERROR_MALLOC_FAIL);
	skip_rgb_whitespace(rgb_values);
	if (!rgb_values[0] \
	|| !rgb_values[1] \
	|| !rgb_values[2] \
	|| (ft_strlen(rgb_values[0]) == 0 || ft_strlen(rgb_values[0]) > 4) \
	|| (ft_strlen(rgb_values[1]) == 0 || ft_strlen(rgb_values[1]) > 4) \
	|| (ft_strlen(rgb_values[2]) == 0 || ft_strlen(rgb_values[2]) > 4))
	{
		free_array(rgb_values);
		error_terminate_mlx(cub, ERROR_INVALID_RGB_VAL);
	}
}

void	parse_colors(char *line, uint32_t *color, t_cub *cub)
{
	char	**rgb_values;
	int		r;
	int		g;
	int		b;

	rgb_values = ft_split(line + 2, ',');
	check_colors(rgb_values, cub);
	r = ft_atoi(rgb_values[0]);
	g = ft_atoi(rgb_values[1]);
	b = ft_atoi(rgb_values[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_array(rgb_values);
		error_terminate_mlx(cub, ERROR_INVALID_RGB_VAL);
	}
	*color = (r << 24) | (g << 16) | b << 8;
	free_array(rgb_values);
	cub->colors_set++;
}

void	parse_textures(char *line, t_cub *cub)
{
	if (strncmp(line, "NO ", 3) == 0)
	{
		cub->textures.north_path = ft_strdup(line + 3);
		check_texture(cub->textures.north_path, cub);
	}
	else if (strncmp(line, "SO ", 3) == 0)
	{
		cub->textures.south_path = ft_strdup(line + 3);
		check_texture(cub->textures.south_path, cub);
	}
	else if (strncmp(line, "WE ", 3) == 0)
	{
		cub->textures.west_path = ft_strdup(line + 3);
		check_texture(cub->textures.west_path, cub);
	}
	else if (strncmp(line, "EA ", 3) == 0)
	{
		cub->textures.east_path = ft_strdup(line + 3);
		check_texture(cub->textures.east_path, cub);
	}
	else
		error_terminate_mlx(cub, ERROR_INVALID_FILE_NAME);
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
		error_terminate_mlx(cub, ERROR_MALLOC_FAIL);
	i = 0;
	while (lines[i])
	{
		cub->map[i] = ft_strdup(lines[i]);
		i++;
	}
	cub->map[i] = NULL;
	calculate_map_width(cub);
}

int	parse_cub_file(t_cub *cub, char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (strncmp(lines[i], "NO ", 3) == 0 || strncmp(lines[i], "SO ", 3) == 0
			||strncmp(lines[i], "WE ", 3) == 0 || strncmp(lines[i], "EA ", 3) == 0)
			parse_textures(lines[i], cub);
		else if (strncmp(lines[i], "F ", 2) == 0)
			parse_colors(lines[i], &cub->floor_color, cub);
		else if (strncmp(lines[i], "C ", 2) == 0)
			parse_colors(lines[i], &cub->ceiling_color, cub);
		else if (lines[i][0] == '1' || lines[i][0] == ' ')
		{
			copy_map(&lines[i], cub);
			is_map_valid(cub);
			break ;
		}
		else
			error_terminate_mlx(cub, ERROR_INVALID_FILE);
		i++;
	}
}
