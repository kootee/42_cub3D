/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_content_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:27 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/21 14:10:28 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	set_player_direction(t_cub *cub, char p_char)
{
	if (p_char == 'N')
	{
		cub->player.dir = (t_vector){0.0, -1.0};
		cub->player.plane_x = 0.66;
		cub->player.plane_y = 0.0;
	}
	else if (p_char == 'S')
	{
		cub->player.dir = (t_vector){0.0, 1.0};
		cub->player.plane_x = -0.66;
		cub->player.plane_y = 0.0;
	}
	else if (p_char == 'E')
	{
		cub->player.dir = (t_vector){1.0, 0.0};
		cub->player.plane_x = 0.0;
		cub->player.plane_y = 0.66;
	}
	else if (p_char == 'W')
	{
		cub->player.dir = (t_vector){-1.0, 0.0};
		cub->player.plane_x = 0.0;
		cub->player.plane_y = -0.66;
	}
}

int	check_empty_lines(char **map)
{
	int	row;

	row = 0;
	while (map[row])
	{
		if (strlen(map[row]) == 0)
			return (1);
		row++;
	}
	return (0);
}

int	is_valid_position(char **map, int row, int col)
{
	if (row < 0 || !map[row])
		return (0);
	if (col < 0 || col >= (int)strlen(map[row]))
		return (0);
	return (1);
}
