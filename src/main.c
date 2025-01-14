/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:32:07 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/14 14:36:19 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	init_game(t_cub *cub)
{
	load_textures(cub);
	cub->mlx = mlx_init(WIN_X, WIN_Y, "Cub3D", true);
	if (cub->mlx == NULL)
		handle_error(mlx_errno);
	cub->mlx_img = mlx_new_image(cub->mlx, WIN_X, WIN_Y);
	if (cub->mlx_img == NULL)
		error_terminate_mlx(cub, mlx_errno);
	if (mlx_image_to_window(cub->mlx, cub->mlx_img, 0, 0) < 0)
		error_terminate_mlx(cub, mlx_errno);
	printf("****Game started****\n");
	printf("map_width: %zu\n", cub->map_width);
	printf("player.ppos.x: %f\n", cub->player.ppos.x);
	printf("player.ppos.y: %f\n", cub->player.ppos.y);
	printf("player.dir.x: %f\n", cub->player.dir.x);
	printf("player.dir.y: %f\n", cub->player.dir.y);
	printf("player.plane_x: %f\n", cub->player.plane_x);
	printf("player.plane_y: %f\n", cub->player.plane_y);
}

static void	ft_key_hook(void *param)
{
	t_cub	*cub;
	mlx_t	*mlx_inst;
	char	**map;

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

static void	ft_game_hook(void *param)
{
	t_cub	*cub;

	cub = (t_cub *)param;
	ray_cast(cub);
	draw_minimap(cub);
}

static void	game_loop(t_cub *cub)
{
	mlx_loop_hook(cub->mlx, &ft_key_hook, cub);
	mlx_loop_hook(cub->mlx, &ft_game_hook, cub);
	mlx_loop(cub->mlx);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

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
