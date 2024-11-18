/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 17:17:23 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
// add temp 5x5 map
void    add_temp_data(t_cub *cub)
{
    cub->map = ft_calloc(6, sizeof(char *));
    cub->map[0] = ft_strdup("11111");
    cub->map[1] = ft_strdup("10001");
    cub->map[2] = ft_strdup("10P01");
    cub->map[3] = ft_strdup("10001");
    cub->map[4] = ft_strdup("11111");
    cub->map[5] = NULL;
}

void    init_game(t_cub * cub)
{
    // initialise structs etc
}

void    load_map(char *map_data)
{
    // implement
    // check map
    // load data to map variable   
}

// add player data: location in map, ray direction
void    init_player(t_cub *cub)
{
    // THIS IS TEMP DATA, CHANGE LATER
    cub->player.ppos.x_dir = 3;
    cub->player.ppos.y_dir = 3;
    cub->player.dir.x_dir = -1;
    cub->player.dir.y_dir = 0;
    cub->player.plane_x = 0;
    cub->player.plane_y = 0.66;
}

void  load_textures(t_cub *cub)
{
    cub->textures.north = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/north.png");
    if (cub->textures.north == NULL)
      handle_error(ERROR_TEXTURE);
    cub->textures.south = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/south.png");
    if (cub->textures.south == NULL)
      handle_error(ERROR_TEXTURE);
    cub->textures.east = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/east.png");
    if (cub->textures.east == NULL)
      handle_error(ERROR_TEXTURE);
    cub->textures.west = mlx_load_png("/Users/katjatoivola/Desktop/DOCS/Hive/Projects/cub3D/textures/west.png");
    if (cub->textures.west == NULL)
      handle_error(ERROR_TEXTURE);
}

void	init_cub(t_cub *cub, char *map_data, int argc)
{
  if (argc != 2)
		handle_error(ERROR_CMD_COUNT_ERROR);
    cub->mlx = mlx_init(WIN_X, WIN_Y, "Cub3D", true);
	if (cub->mlx == NULL)
		handle_error(mlx_errno);
    cub->mlx_img = mlx_new_image(cub->mlx, WIN_X, WIN_Y);
	if (cub->mlx_img == NULL)
		error_terminate_mlx(cub, mlx_errno);
  if (mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
  add_temp_data(cub); // THIS IS A TEMP MAP, REMOVE LATER
  init_game(cub);
  init_player(cub);
  load_map(map_data);
  load_textures(cub);
}
