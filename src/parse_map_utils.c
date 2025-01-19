/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 14:25:00 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/18 16:35:11 by ktoivola         ###   ########.fr       */
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
