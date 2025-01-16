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

void	set_player_direction(t_cub *cub, char p_char)
{
	if (p_char == 'N')
	{
		cub->player.dir = (t_vector){0.0, -1.0}, 
		cub->player.plane_x = 0.66,
		cub->player.plane_y = 0.0;
	}
	else if (p_char == 'S')
	{
		cub->player.dir = (t_vector){0.0, 1.0}, 
		cub->player.plane_x = -0.66,
		cub->player.plane_y = 0.0;
	}
	else if (p_char == 'E')
	{
		cub->player.dir = (t_vector){1.0, 0.0},
		cub->player.plane_x = 0.0,
		cub->player.plane_y = 0.66;
	}
	else if (p_char == 'W')
	{
		cub->player.dir = (t_vector){-1.0, 0.0}, 
		cub->player.plane_x = 0.0, 
		cub->player.plane_y = -0.66;
	}
}

int validate_and_set_player(t_cub *cub, int r, int c, char p_char)
{
	static int player_count;

	player_count = 0;
	player_count++;
	if (player_count > 1)
	{
		fprintf(stderr, "Error\nMap must have exactly one player.\n");
		return (1);
	}
	cub->player.ppos = (t_vector){c + 0.5, r + 0.5};
	printf("Player position set: x=%f, y=%f\n", cub->player.ppos.x, cub->player.ppos.y);
	
	set_player_direction(cub, p_char);
	return (0);
}



int validate_player_position(t_cub *cub)
{
	size_t i, j;
	int p_count = 0;

	for (i = 0; i < cub->map_height; i++)
	{
		for (j = 0; cub->map[i][j]; j++)
		{
			if (is_player_char(cub->map[i][j]))
			{
				p_count++;
				if (validate_and_set_player(cub, i, j, cub->map[i][j]))
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
		&& cell != 'E' && cell != 'W' && cell != ' ')
	{
		fprintf(stderr, "Error: Invalid character '%c' at row %d, col %d.\n", cell, row, col);
		return (1);
	}
	return (0);
}

int	count_players(char **map, int *p_count, int row, int col, t_cub *cub)
{
	char	cell;

	cell = map[row][col];
	if (cell == 'N' || cell == 'S' || cell == 'E' || cell == 'W')
	{
		(*p_count)++;
		if (*p_count > 1)
		{
			fprintf(stderr, "Error: Multiple players found.\n");
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
	{
		fprintf(stderr, "Error: Map is empty.\n");
		return ;
	}
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
			fprintf(stderr, "Error: Map is not closed at row %d, col %d.\n", row, col);
			return (1);
		}
	}
	return (0);
}

int	check_map_is_empty(t_cub *cub)
{
	if (!cub->map || !cub->map[0])
	{
		fprintf(stderr, "Error: Map is empty.\n");
		return (1);
	}
	return (0);
}

int	validate_map_content(t_cub *cub, int *p_count)
{
	int	row;
	int	col;

	row = 0;
	while (cub->map[row])
	{
		col = 0;
		while (cub->map[row][col])
		{
			if (check_valid_characters(cub->map, row, col)
				||check_map_closure(cub->map, row, col)
				||count_players(cub->map, p_count, row, col, cub))
				return (1);
			col++;
		}
		row++;
	}
	return (0);
}

int	is_map_valid(t_cub *cub)
{
	int	p_count;

	p_count = 0;
	if (check_map_is_empty(cub) || check_empty_lines(cub->map)
		||validate_map_content(cub, &p_count))
		return (1);
	if (p_count == 0)
	{
		fprintf(stderr, "Error: No player found on the map.\n");
		return (1);
	}
	return (0);
}
