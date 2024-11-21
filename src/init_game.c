/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/21 14:44:12 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

void    init_game(t_cub * cub)
{
    // initialise structs and variables
    // THIS IS TEMP DATA, CHANGE LATER
    cub->ceiling_color = MAGENTA;
    cub->floor_color = LIGHTBLUE;
}

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

void check_file_exists(const char *filepath) {
    if (access(filepath, F_OK) != 0) {
        fprintf(stderr, "Error: File %s does not exist. Errno: %d, %s\n", filepath, errno, strerror(errno));
        printf("File does not exist");
        exit(1);
    }
}

void load_textures(t_cub *cub)
{
    const char *north_path = "/home/ktoivola/Projects/cub3D/textures/north.png";
    const char *south_path = "/home/ktoivola/Projects/cub3D/textures/north.png";
    const char *east_path = "/home/ktoivola/Projects/cub3D/textures/north.png";
    const char *west_path = "/home/ktoivola/Projects/cub3D/textures/north.png";

    check_file_exists(north_path);
    cub->textures.north = mlx_load_png(north_path);
    if (cub->textures.north == NULL) {
        fprintf(stderr, "Failed to load texture: %s\n", north_path);
        printf("Failed to load north texture");
        exit(1);
    }

    check_file_exists(south_path);
    cub->textures.south = mlx_load_png(south_path);
    if (cub->textures.south == NULL) {
        fprintf(stderr, "Failed to load texture: %s\n", south_path);
        printf("Failed to load south texture");
        exit(1);
    }

    check_file_exists(east_path);
    cub->textures.east = mlx_load_png(east_path);
    if (cub->textures.east == NULL) {
        fprintf(stderr, "Failed to load texture: %s\n", east_path);
        printf("Failed to load east texture");
        exit(1);
    }

    check_file_exists(west_path);
    cub->textures.west = mlx_load_png(west_path);
    if (cub->textures.west == NULL) {
        fprintf(stderr, "Failed to load texture: %s\n", west_path);
        printf("Failed to load west texture");
        exit(1);
    }
}

void	init_cub(t_cub *cub, char **argv, int argc)
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
  parse_map(argv[1]); // IMPLEMENT
  init_game(cub);
  init_player(cub);
  load_map(cub);
  load_textures(cub);
}
