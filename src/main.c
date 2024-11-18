/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 17:01:41 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    terminate_cub(t_cub *cub)
{
    // free all allocated memory and clean mlx
    mlx_delete_image(cub->mlx, cub->mlx_img);
	mlx_terminate(cub->mlx);
}

void    game_loop(t_cub *cub)
{
    mlx_loop_hook(cub->mlx, ft_hook, &cub);
	mlx_loop(cub->mlx);
    ray_cast(&cub);
}

int	main(int argc, char **argv)
{
    t_cub   cub;
    
	init_cub(&cub, argv, argc);
    game_loop(&cub);
    terminate_cub(&cub);
	return (EXIT_SUCCESS);
}