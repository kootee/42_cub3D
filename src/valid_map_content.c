#include "cub3D.h"

static int	is_valid_map_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S' || 
			c == 'E' || c == 'W' || c == ' ');
}

static int	check_map_content(t_cub *cub)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (!is_valid_map_char(cub->map[i][j]))
			{
				fprintf(stderr, "Error\nInvalid character '%c' in map.\n", cub->map[i][j]);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

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
		if (cub->map[cub->map_height - 1][i] != '1' && cub->map[cub->map_height - 1][i] != ' ')
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

int	validate_player_position(t_cub *cub)
{
	size_t	i;
	size_t	j;
	int		player_count;

	i = 0;
	player_count = 0;
	while (i < cub->map_height)
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (is_player_char(cub->map[i][j]))
			{
				cub->player.ppos.x = j;
				cub->player.ppos.y = i;
				if(cub->map[i][j] == 'N')
				{
					cub->player.dir.x = 0.0;
					cub->player.dir.y = -1.0;
					cub->player.plane_x = 0.66;
					cub->player.plane_y = 0.0;
				}
				if(cub->map[i][j] == 'S')
				{
					cub->player.dir.x = 0.0;
					cub->player.dir.y = 1.0;
					cub->player.plane_x = -0.66;
					cub->player.plane_y = 0.0;
				}
				if(cub->map[i][j] == 'E')
				{
					cub->player.dir.x = 1.0;
					cub->player.dir.y = 0.0;
					cub->player.plane_x = 0.0;
					cub->player.plane_y = 0.66;
				}
				if(cub->map[i][j] == 'W')
				{
					cub->player.dir.x = -1.0;
					cub->player.dir.y = 0.0;
					cub->player.plane_x = 0.0;
					cub->player.plane_y = -0.66;
				}

				// cub->player.p_angle = (cub->map[i][j] == 'N') ? -M_PI_2 :
				// 					  (cub->map[i][j] == 'S') ? M_PI_2 :
				// 					  (cub->map[i][j] == 'E') ? 0 :
				// 					  M_PI;
				player_count++;
			}
			j++;
		}
		i++;
	}
	if (player_count != 1)
	{
		fprintf(stderr, "Error\nMap must have exactly one player start.\n");
		return (1);
	}
	return (0);
}


int is_map_valid(t_cub *cub)
{
    if (!cub->map)
    {
        fprintf(stderr, "Error\nMap is empty or invalid.\n");
        return (1);
    }

    if (check_map_content(cub) || check_map_boundaries(cub) || validate_player_position(cub))
    {
		return (1);
	}
    return (0);
}

