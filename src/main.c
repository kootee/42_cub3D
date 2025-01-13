/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/13 17:19:11 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

void	ft_game_hook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
    ray_cast(cub);
	draw_minimap(cub);
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

void    game_loop(t_cub *cub)
{
    mlx_loop_hook(cub->mlx, &ft_key_hook, cub);
    mlx_loop_hook(cub->mlx, &ft_game_hook, cub);
	mlx_loop(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub cub;

	init_main_struct(&cub);
	if (handle_arguments(argc, argv) == 1)
	{
		return (1);
	}
	if (create_file(&cub, argv[1]) == 1)
	{
		return (1);
	}
	if (is_map_valid(&cub) == 1)
	{
		return (1);
	}
	init_game(&cub);
    game_loop(&cub);
    free_all_resources(&cub);
	return (EXIT_SUCCESS);
}

