/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:23:49 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/19 14:46:51 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_game(t_cub *cub)
{
	load_textures(cub);
	cub->mlx = mlx_init(WIN_X, WIN_Y, "Cub3D", false);
	if (cub->mlx == NULL)
		handle_error(mlx_errno);
	cub->mlx_img = mlx_new_image(cub->mlx, WIN_X, WIN_Y);
	if (cub->mlx_img == NULL)
		error_terminate_mlx(cub, mlx_errno);
	if (mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
	printf("****Game started****\n");
	printf("map_width: %zu\n", cub->map_width);
	printf("player.ppos.x: %f\n", cub->player.ppos.x);
	printf("player.ppos.y: %f\n", cub->player.ppos.y);
	printf("player.dir.x: %f\n", cub->player.dir.x);
	printf("player.dir.y: %f\n", cub->player.dir.y);
	printf("player.plane_x: %f\n", cub->player.plane_x);
	printf("player.plane_y: %f\n", cub->player.plane_y);
}

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
	cub->colors_set = 0;
	init_player_struct(cub);
	init_ray_struct(cub);
	init_textures_and_map(cub);
}
