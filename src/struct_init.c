/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:23:49 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/17 19:05:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_player_struct(t_cub *cub)
{
	cub->player.ppos.x = 0.0;
	cub->player.ppos.y = 0.0;
	cub->player.dir.x = 0.0;
	cub->player.dir.y = 0.0;
	cub->player.p_angle = 0.0;
	cub->player.plane_x = 0.0;
	cub->player.plane_y = 0.0;
}

static void	init_ray_struct(t_cub *cub)
{
	cub->ray.d_dist.x = 0.0;
	cub->ray.d_dist.y = 0.0;
	cub->ray.step.x = 0.0;
	cub->ray.step.y = 0.0;
	cub->ray.side_dist.x = 0.0;
	cub->ray.side_dist.y = 0.0;
	cub->ray.map_coord.x_coord = 0;
	cub->ray.map_coord.y_coord = 0;
	cub->ray.dir.x = 0.0;
	cub->ray.dir.y = 0.0;
	cub->ray.wall_dist = 0.0;
	cub->ray.wall_x = 0.0;
	cub->ray.side = -1;
}

static void	init_textures_and_map(t_cub *cub)
{
	cub->map = NULL;
	cub->map_height = 0;
	cub->map_width = 0;
	cub->ceiling_color = 0;
	cub->floor_color = 0;
	cub->textures.north = NULL;
	cub->textures.south = NULL;
	cub->textures.east = NULL;
	cub->textures.west = NULL;
	cub->textures.north_path = NULL;
	cub->textures.south_path = NULL;
	cub->textures.east_path = NULL;
	cub->textures.west_path = NULL;
}

void	init_main_struct(t_cub *cub)
{
	cub->mlx = NULL;
	cub->mlx_img = NULL;
	cub->map_file_lines = NULL;
	init_player_struct(cub);
	init_ray_struct(cub);
	init_textures_and_map(cub);
}
