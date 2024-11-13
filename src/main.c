/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/13 20:00:54 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_cub3d(t_cub *cub)
{
    cub->mlx = mlx_init(WIN_X, WIN_Y, "cube3D", true);
	if (cub->mlx == NULL)
		handle_error(&cub->map, mlx_errno);
	cub->img = mlx_new_image(cub->mlx, WIN_X, WIN_Y);
	if (cub->img == NULL)
		error_terminate_mlx(cub, mlx_errno);
	if (mlx_image_to_window(cub->mlx, cub->img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
}

static void	ft_hook(void *param)
{
	t_cub	*cub;
	mlx_t	*mlx_inst;

	cub = param;
	mlx_inst = cub->mlx;
	if (mlx_is_key_down(cub->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(cub->mlx);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_LEFT))
		mlx_close_window(cub->mlx); // implement look left
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		mlx_close_window(cub->mlx); // implement look right
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		mlx_close_window(cub->mlx); // implement move
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		mlx_close_window(cub->mlx); // implement move
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		mlx_close_window(cub->mlx); // implement move
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		mlx_close_window(cub->mlx); // implement move
}

int	main(int argc, char **argv)
{
    t_cub   cub;
    
	if (argc != 2)
		handle_error(NULL, EXIT_CMD_COUNT_ERROR);
	load_map(argv[1]); // set some default map content
	init_cube3D(&cub);
	draw_map(&cub);
	mlx_loop_hook(cub.mlx, ft_hook, &cub);
	mlx_loop(cub.mlx);
    // free 
	mlx_terminate(cub.mlx);
	return (EXIT_SUCCESS);
}