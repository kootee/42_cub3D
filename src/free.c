/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:09:25 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/18 15:47:07 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_all_resources(t_cub *cub)
{
	if (cub->map)
		free_array(cub->map);
	if (cub->map_file_lines)
		free_array(cub->map_file_lines);
	if (cub->textures.north_path)
		free(cub->textures.north_path);
	if (cub->textures.south_path)
		free(cub->textures.south_path);
	if (cub->textures.west_path)
		free(cub->textures.west_path);
	if (cub->textures.east_path)
		free(cub->textures.east_path);
	if (cub->textures.north)
		mlx_delete_texture(cub->textures.north);
	if (cub->textures.south)
		mlx_delete_texture(cub->textures.south);
	if (cub->textures.east)
		mlx_delete_texture(cub->textures.east);
	if (cub->textures.west)
		mlx_delete_texture(cub->textures.west);
	if (cub->mlx_img)
		mlx_delete_image(cub->mlx, cub->mlx_img);
	if (cub->mlx)
		mlx_terminate(cub->mlx);
}

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
	array = NULL;
}
