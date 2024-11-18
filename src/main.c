/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 15:33:21 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    terminate_cub(t_cub *cub)
{
    // free all allocated memory and clean mlx
    mlx_delete_image(cub->mlx, cub->mlx_img);
	mlx_terminate(cub->mlx);
}

// Loops game: raycasting ang image drawing
void    game_loop(t_cub *cub)
{
    mlx_t   *mlx;
    
    mlx = cub->mlx;
    mlx_delete_image(mlx, cub->mlx_img);
    cub->mlx_img = mlx_new_image(mlx, WIN_X, WIN_Y);
	if (cub->mlx_img == NULL)
		error_terminate_mlx(cub, mlx_errno);
    mlx_loop_hook(cub->mlx, ft_hook, &cub);
	mlx_loop(cub->mlx);
    ray_cast(&cub);
    if (mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
}

int	main(int argc, char **argv)
{
    t_cub   cub;
    
	init_cub(&cub, argv, argc);
    game_loop(&cub);
    terminate_cub(&cub);
	return (EXIT_SUCCESS);
}