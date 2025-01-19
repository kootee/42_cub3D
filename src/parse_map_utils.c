/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:25:00 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/19 17:42:15 by psitkin          ###   ########.fr       */
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
