/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_map_content.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 14:10:49 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/21 14:32:55 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
			ft_putstr_fd("Multiple players found.\n", STDERR_FILENO);
			return (1);
		}
		cub->player.ppos.x = col + 0.5;
		cub->player.ppos.y = row + 0.5;
		set_player_direction(cub, cell);
	}
	return (0);
}

int	check_map_closure(char **map, int row, int col)
{
	char	cell;

	cell = map[row][col];
	if (cell == '0' || cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		if (!is_valid_position(map, row - 1, col) || map[row - 1][col] == ' ' ||
			!is_valid_position(map, row + 1, col) || map[row + 1][col] == ' ' ||
			!is_valid_position(map, row, col - 1) || map[row][col - 1] == ' ' ||
			!is_valid_position(map, row, col + 1) || map[row][col + 1] == ' ')
		{
			return (1);
		}
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
		handle_error(ERROR_INVALID_PLAYER);
}
