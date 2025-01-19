#include "cub3D.h"

static int	check_top_and_bottom_rows(t_cub *cub)
{
	size_t	i;

	i = 0;
	while (cub->map[0][i])
	{
		if (cub->map[0][i] != '1' && cub->map[0][i] != ' ')
			return (1);
		i++;
	}
	i = 0;
	while (cub->map[cub->map_height - 1][i])
	{
		if (cub->map[cub->map_height - 1][i] != '1'
			&& cub->map[cub->map_height - 1][i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

static int	check_middle_rows(t_cub *cub)
{
	size_t	i;
	size_t	len;

	i = 1;
	while (i < cub->map_height - 1)
	{
		len = strlen(cub->map[i]);
		if (cub->map[i][0] != '1' || cub->map[i][len - 1] != '1')
			return (1);
		i++;
	}
	return (0);
}

int	check_map_boundaries(t_cub *cub)
{
	if (check_top_and_bottom_rows(cub) || check_middle_rows(cub))
	{
		fprintf(stderr, "Error\nMap is not surrounded by walls.\n");
		return (1);
	}
	return (0);
}

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
			fprintf(stderr, "Row %d, col %d\n", row, col);
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
