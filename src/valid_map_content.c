/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 13:43:12 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/21 13:46:06 by ktoivola         ###   ########.fr       */
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

int	is_valid_position(char **map, int row, int col)
{
	if (row < 0 || !map[row])
		return (0);
	if (col < 0 || col >= (int)strlen(map[row]))
		return (0);
	return (1);
}

int	check_valid_characters(char **map, int row, int col)
{
	char	cell;

	cell = map[row][col];
	if (cell != '0' && cell != '1' && cell != 'N' && cell != 'S'
		&& cell != 'E' && cell != 'W' && cell != ' ' && cell != '\t')
	{
		return (1);
	}
	return (0);
}

int	count_players(t_cub *cub, int *p_count, int row, int col)
{
	char	cell;

	cell = cub->map[row][col];
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		(*p_count)++;
		if (*p_count > 1)
		{
			ft_putstr_fd("Multiple players found.\n", 1);
			return (1);
		}
		cub->player.ppos.x = col + 0.5;
		cub->player.ppos.y = row + 0.5;
		set_player_direction(cub, cell);
	}
	return (0);
}

void	is_map_valid(t_cub *cub)
{
	int	row;
	int	col;
	int	p_count;

	p_count = 0;
	if (!cub->map || !cub->map[0] || check_empty_lines(cub->map))
		error_terminate_mlx(cub, ERROR_INVALID_MAP_PTS);
	row = 0;
	while (cub->map[row])
	{
		col = 0;
		while (cub->map[row][col])
		{
			if (check_valid_characters(cub->map, row, col))
				error_terminate_mlx(cub, ERROR_INVALID_CHARACTER);
			if (check_map_closure(cub->map, row, col))
				error_terminate_mlx(cub, ERROR_UNCLOSED_MAP);
			if (count_players(cub, &p_count, row, col))
				error_terminate_mlx(cub, ERROR_INVALID_PLAYER);
			col++;
		}
		row++;
	}
	if (p_count == 0)
		error_terminate_mlx(cub, ERROR_INVALID_PLAYER);
}
