/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/21 16:15:53 by ktoivola         ###   ########.fr       */
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

void	ft_game_hook(void *param)
{
	t_cub	*cub;

	cub = param;
    ray_cast(cub);
	mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0);
}

void    game_loop(t_cub *cub)
{
    mlx_loop_hook(cub->mlx, ft_key_hook, &cub);
    mlx_loop_hook(cub->mlx, ft_game_hook, &cub);
	mlx_loop(cub->mlx);
}

int	main(int argc, char **argv)
{
    t_cub   *cub;
    
	init_game(cub, argv, argc);
    game_loop(cub);
    terminate_cub(cub);
	return (EXIT_SUCCESS);
}