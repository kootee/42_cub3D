/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/21 16:26:09 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h> // Remove later
#include <errno.h> // Remove later
#include <string.h> // Remove later
#include <unistd.h> // Remove later

void    load_map(t_cub *cub)
{
    // implement
    // check map
    // load data to map variable (type char **map)
    cub->map = ft_calloc(6, sizeof(char *));
    cub->map[0] = ft_strdup("11111");
    cub->map[1] = ft_strdup("10001");
    cub->map[2] = ft_strdup("10P01");
    cub->map[3] = ft_strdup("10001");
    cub->map[4] = ft_strdup("11111");
    cub->map[5] = NULL; 
    for (int i = 0; cub->map[i] != NULL; i++)
    {
        printf("%s\n", cub->map[i]);
    }
}

// add player data: location in map, ray direction
void    init_player(t_cub *cub)
{
    // THIS IS TEMP DATA, CHANGE LATER
    cub->player.ppos.x = 3;
    cub->player.ppos.y = 3;
    cub->player.dir.x = -1;
    cub->player.dir.y = 0;
    cub->player.plane_x = 0;
    cub->player.plane_y = 0.66;
}

void    init_cub(t_cub * cub)
{
    // initialise structs and variables
    cub = malloc(sizeof(t_cub));
    init_player(cub);
    load_map(cub);
    // THIS IS TEMP DATA, CHANGE LATER
    cub->ceiling_color = MAGENTA;
    cub->floor_color = LIGHTBLUE;
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

void	init_game(t_cub *cub, char **argv, int argc)
{
  if (argc != 2)
		handle_error(ERROR_CMD_COUNT_ERROR);
  parse_map(argv[1]); // IMPLEMENT
  init_cub(cub);
  load_textures(cub);
  cub->mlx = mlx_init(WIN_X, WIN_Y, "Cub3D", true);
	if (cub->mlx == NULL)
		handle_error(mlx_errno);
  cub->mlx_img = mlx_new_image(cub->mlx, WIN_X, WIN_Y);
	if (cub->mlx_img == NULL)
		error_terminate_mlx(cub, mlx_errno);
  if (mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
}
