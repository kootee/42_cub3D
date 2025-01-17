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

static int	is_player_char(char c)
{
	return (c == 'N' || c == 'S' || c == 'E' || c == 'W');
}

int	validate_and_set_player(t_cub *cub, int r, int c, char p_char, int *p_count)
{
	*p_count += 1;
	if (*p_count > 1)
	{
		fprintf(stderr, "Error\nMap must have exactly one player.\n");
		return (1);
	}
	cub->player.ppos.x = c;
	cub->player.ppos.y = r;
	printf("Player position set: x=%f, y=%f\n", cub->player.ppos.x, cub->player.ppos.y);
	if (p_char == 'N')
	{
		cub->player.dir.x = 0.0;
		cub->player.dir.y = -1.0;
		cub->player.plane_x = 0.66;
		cub->player.plane_y = 0.0;
	}
	else if (p_char == 'S')
	{
		cub->player.dir.x = 0.0;
		cub->player.dir.y = 1.0;
		cub->player.plane_x = -0.66;
		cub->player.plane_y = 0.0;
	}
	else if (p_char == 'E')
	{
		cub->player.dir.x = 1.0;
		cub->player.dir.y = 0.0;
		cub->player.plane_x = 0.0;
		cub->player.plane_y = 0.66;
	}
	else if (p_char == 'W')
	{
		cub->player.dir.x = -1.0;
		cub->player.dir.y = 0.0;
		cub->player.plane_x = 0.0;
		cub->player.plane_y = -0.66;
	}
	return (0);
}

int	validate_player_position(t_cub *cub)
{
	size_t	i;
	size_t	j;
	int		p_count;

	p_count = 0;
	for (i = 0; i < cub->map_height; i++)
	{
		for (j = 0; cub->map[i][j]; j++)
		{
			if (is_player_char(cub->map[i][j]))
			{
				if (validate_and_set_player(cub, i, j, cub->map[i][j], &p_count))
					return (1);
			}
		}
	}
	if (p_count != 1)
	{
		fprintf(stderr, "Error\nMap must have exactly one player start.\n");
		return (1);
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

int	check_valid_characters(char **map, int row, int col)
{
	char	cell;

	cell = map[row][col];
	if (cell != '0' && cell != '1' && cell != 'N' && cell != 'S'
		&& cell != 'E' && cell != 'W' && cell != ' ' && cell != '\t')
	{
		fprintf(stderr, "Error: Invalid character '%c' at row %d, col %d.\n", cell, row, col);
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
		if (cell == 'N')
		{
			cub->player.dir.x = 0.0;
			cub->player.dir.y = -1.0;
			cub->player.plane_x = 0.66;
			cub->player.plane_y = 0.0;
		}
		else if (cell == 'S')
		{
			cub->player.dir.x = 0.0;
			cub->player.dir.y = 1.0;
			cub->player.plane_x = -0.66;
			cub->player.plane_y = 0.0;
		}
		else if (cell == 'E')
		{
			cub->player.dir.x = 1.0;
			cub->player.dir.y = 0.0;
			cub->player.plane_x = 0.0;
			cub->player.plane_y = 0.66;
		}
		else if (cell == 'W')
		{
			cub->player.dir.x = -1.0;
			cub->player.dir.y = 0.0;
			cub->player.plane_x = 0.0;
			cub->player.plane_y = -0.66;
		}
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
		{
			fprintf(stderr, "Error: Empty line in map at row %d.\n", row);
			return (1);
		}
		row++;
	}
	return (0);
}

void	calculate_map_width(t_cub *cub)
{
	int		row;
	size_t	max_width;
	size_t	current_width;

	max_width = 0;
	if (!cub->map || !cub->map[0])
		error_terminate_mlx(cub, ERROR_INVALID_MAP);
	row = 0;
	while (cub->map[row])
	{
		current_width = strlen(cub->map[row]);
		if (current_width > max_width)
			max_width = current_width;
		row++;
	}
	cub->map_width = max_width;
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
				error_terminate_mlx(cub, ERROR_INVALID_PLAYER);
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
