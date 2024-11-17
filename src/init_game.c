/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 17:07:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/17 17:34:30 by ktoivola         ###   ########.fr       */
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
    cub->player->ppos.x_coord = 3;
    cub->player->ppos.y_coord = 3;
}

static void	init_cub3d(t_cub *cub, char *map_data)
{
    // temporary filling the data
    add_temp_data(cub);
    // remove after init is added
    load_map(map_data);
    init_player();
    
    // start mlx and open window
    cub->mlx = mlx_init(WIN_X, WIN_Y, "cube3D", true);
	if (cub->mlx == NULL)
		handle_error(&cub->map, mlx_errno);
	cub->mlx_img = mlx_new_image(cub->mlx, WIN_X, WIN_Y);
	if (cub->mlx_img == NULL)
		error_terminate_mlx(cub, mlx_errno);
	if (mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
}

void    load_map(char *map_data)
{
    // implement
    // check map
    // load data to map variable   
}

void    init_player()
{
    // implement
    // set player pos and dir based on map data
}