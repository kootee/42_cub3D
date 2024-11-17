/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/17 17:12:10 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
// Loops raycasting ang image drawing
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
    cast_rays(&cub);
    if (mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
}

int	main(int argc, char **argv)
{
    t_cub   cub;
    
	if (argc != 2)
		handle_error(NULL, EXIT_CMD_COUNT_ERROR);
	init_cube3D(&cub, argv[1]);
    
    // free and terminate
    mlx_delete_image(cub.mlx, cub.mlx_img);
	mlx_terminate(cub.mlx);
	return (EXIT_SUCCESS);
}