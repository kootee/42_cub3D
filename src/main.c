/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/12/04 15:37:58 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

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
    t_cub   cub;
    if (validate_arguments(argc, argv) == 1)
    {
        return EXIT_FAILURE;
    }
	init_game(&cub, argv, argc);
    game_loop(&cub);
    terminate_cub(&cub);
	return (EXIT_SUCCESS);
}