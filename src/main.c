/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/23 11:02:44 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    terminate_cub(t_cub *cub)
{
    // free all allocated memory and clean mlx
	int i = -1;
	while (cub->map[++i] != NULL)
		free(cub->map[i]);
	free(cub->map[i]);
	free(cub->map);
    mlx_delete_image(cub->mlx, cub->mlx_img);
	mlx_terminate(cub->mlx);
}


void	ft_key_hook(void *param)
{
	t_cub	*cub;
	mlx_t	*mlx_inst;
    char    **map;

	cub = (t_cub *)param;
	mlx_inst = cub->mlx;
    map = cub->map;
	if (mlx_is_key_down(mlx_inst, MLX_KEY_ESCAPE))
		mlx_close_window(mlx_inst);
	if (mlx_is_key_down(mlx_inst, MLX_KEY_LEFT))
		left_key(cub);
	if (mlx_is_key_down(mlx_inst, MLX_KEY_RIGHT))
		right_key(cub);
	if (mlx_is_key_down(mlx_inst, MLX_KEY_W))
		w_key(cub);
	if (mlx_is_key_down(mlx_inst, MLX_KEY_A))
		a_key(cub);
	if (mlx_is_key_down(mlx_inst, MLX_KEY_S))
		s_key(cub);
	if (mlx_is_key_down(mlx_inst, MLX_KEY_D))
		d_key(cub);
}

void	draw_minimap_square(t_cub *cub ,t_vector map_pt, size_t size)
{
	for (size_t y = map_pt.y; y <= (map_pt.y + size); y++)
	{
		for (size_t x = map_pt.x; x <= (map_pt.x + size); x++)
		{
			
		}
	}
}

void	draw_minimap(t_cub *cub)
{
	t_vector	pt;
	t_vector	map_pt;
	
	for (pt.y = 0; pt.y < cub->map_height; pt.y++)
	{
		for (pt.x = 0; pt.x < cub->map_width; pt.x++)
		{
			map_pt.y = pt.y * 40;
			map_pt.x = pt.x * 40;
			draw_minimap_square(cub, map_pt, 40);
		}
	}
	draw_player(cub);
}

void	ft_game_hook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	draw_minimap(cub);
    ray_cast(cub);
}

void    game_loop(t_cub *cub)
{
    mlx_loop_hook(cub->mlx, &ft_key_hook, cub);
    mlx_loop_hook(cub->mlx, &ft_game_hook, cub);
	mlx_loop(cub->mlx);
}

int	main(int argc, char **argv)
{
    t_cub   cub;
    
	init_game(&cub, argv, argc);
    game_loop(&cub);
    terminate_cub(&cub);
	return (EXIT_SUCCESS);
}