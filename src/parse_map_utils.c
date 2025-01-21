/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:25:00 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/21 14:22:42 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	map_floodfill(t_cub *cub)
{
	int		i;
	size_t	j;
	size_t	len_diff;
	char	*fill;
	char	*filled_map_line;

	i = 0;
	while (cub->map[i])
	{
		len_diff = (cub->map_width + 1) - ft_strlen(cub->map[i]);
		if (len_diff > 0)
		{
			j = 0;
			fill = (char *)ft_calloc(len_diff + 1, sizeof(char));
			while (j < len_diff)
				fill[j++] = '0';
			filled_map_line = ft_strjoin(cub->map[i], fill);
			free(cub->map[i]);
			free(fill);
			cub->map[i] = filled_map_line;
		}
		i++;
	}
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
		ft_putstr_fd("Error\nMap is not surrounded by walls.\n", 1);
		return (1);
	}
	return (0);
}
