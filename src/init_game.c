/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:12 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/13 16:39:58 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* void  load_textures(t_cub *cub)
{
    cub->textures.north = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/2/north.png");
    if (cub->textures.north == NULL)
      handle_error(ERROR_TEXTURE);
    cub->textures.south = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/2/south.png");
    if (cub->textures.south == NULL)
      handle_error(ERROR_TEXTURE);
    cub->textures.east = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/2/east.png");
    if (cub->textures.east == NULL)
      handle_error(ERROR_TEXTURE);
    cub->textures.west = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/2/west.png");
    if (cub->textures.west == NULL)
      handle_error(ERROR_TEXTURE);
} */

void	init_game(t_cub *cub)
{
    load_textures(cub);
    cub->mlx = mlx_init(WIN_X, WIN_Y, "Cub3D", true);
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
