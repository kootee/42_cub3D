/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 20:30:29 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/07 20:30:30 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_texture_paths(t_textures *textures)
{
	if (textures->north_path)
		free(textures->north_path);
	if (textures->south_path)
		free(textures->south_path);
	if (textures->west_path)
		free(textures->west_path);
	if (textures->east_path)
		free(textures->east_path);
}

void	free_textures(t_cub *cub)
{
	free_texture_paths(&cub->textures);
	if (cub->textures.north)
		mlx_delete_texture(cub->textures.north);
	if (cub->textures.south)
		mlx_delete_texture(cub->textures.south);
	if (cub->textures.east)
		mlx_delete_texture(cub->textures.east);
	if (cub->textures.west)
		mlx_delete_texture(cub->textures.west);
}

void	load_textures(t_cub *cub)
{
	cub->textures.north = mlx_load_png(cub->textures.north_path);
	if (cub->textures.north == NULL)
		handle_error(ERROR_TEXTURE);
	cub->textures.south = mlx_load_png(cub->textures.south_path);
	if (cub->textures.south == NULL)
		handle_error(ERROR_TEXTURE);
	cub->textures.east = mlx_load_png(cub->textures.east_path);
	if (cub->textures.east == NULL)
		handle_error(ERROR_TEXTURE);
	cub->textures.west = mlx_load_png(cub->textures.west_path);
	if (cub->textures.west == NULL)
		handle_error(ERROR_TEXTURE);
}
