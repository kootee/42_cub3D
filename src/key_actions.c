/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:32:43 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 16:02:04 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    left_key(t_cub *cub)
{
    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->player.dir.x_dir;
    cub->player.dir.x_dir = cub->player.dir.x_dir * cos(ROT_SPEED)
                            - cub->player.dir.y_dir *  sin(ROT_SPEED);
    cub->player.dir.y_dir = old_dirX * sin(ROT_SPEED) + cub->player.dir.y_dir
                            *cos(ROT_SPEED);
    old_planeX = cub->camera_plane.x_dir;
    cub->camera_plane.x_dir = cub->camera_plane.x_dir * cos(ROT_SPEED) 
                            - cub->camera_plane.y_dir * sin(ROT_SPEED);
    cub->camera_plane.y_dir = old_planeX * sin(ROT_SPEED) 
                            + cub->camera_plane.y_dir * cos(ROT_SPEED);
}

void    right_key(t_cub *cub)
{
    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->player.dir.x_dir;
    cub->player.dir.x_dir = cub->player.dir.x_dir * cos(-ROT_SPEED)
                            - cub->player.dir.y_dir *  sin(-ROT_SPEED);
    cub->player.dir.y_dir = old_dirX * sin(-ROT_SPEED) + cub->player.dir.y_dir
                            *cos(-ROT_SPEED);
    old_planeX = cub->camera_plane.x_dir;
    cub->camera_plane.x_dir = cub->camera_plane.x_dir * cos(-ROT_SPEED) 
                            - cub->camera_plane.y_dir * sin(-ROT_SPEED);
    cub->camera_plane.y_dir = old_planeX * sin(-ROT_SPEED) 
                            + cub->camera_plane.y_dir * cos(-ROT_SPEED);
}

void    w_key(t_cub *cub)
{
    double next_x;
    double next_y;
    
    next_x = (int)(cub->player.ppos.x_dir + cub->player.dir.x_dir);
    next_y = (int)(cub->player.ppos.y_dir + cub->player.dir.y_dir);
    if (cub->map[(int)(next_x * PLAYER_SPEED)]
                [(int)(cub->player.ppos.y_dir)] == '0')
        cub->player.ppos.x_dir += cub->player.dir.x_dir * PLAYER_SPEED;
    if (cub->map[(int)(cub->player.ppos.x_dir)]
                [(int)(next_y * PLAYER_SPEED)] == '0')
        cub->player.ppos.y_dir += cub->player.dir.y_dir * PLAYER_SPEED;
}

void    s_key(t_cub *cub)
{
    double prev_x;
    double prev_y;
    
    prev_x = (int)(cub->player.ppos.x_dir - cub->player.dir.x_dir);
    prev_y = (int)(cub->player.ppos.y_dir - cub->player.dir.y_dir);
    if (cub->map[(int)(prev_x * PLAYER_SPEED)]
                [(int)(cub->player.ppos.y_dir)] == '0')
        cub->player.ppos.x_dir += cub->player.dir.x_dir * PLAYER_SPEED;
    if (cub->map[(int)(cub->player.ppos.x_dir)]
                [(int)(prev_y * PLAYER_SPEED)] == '0')
        cub->player.ppos.y_dir += cub->player.dir.y_dir * PLAYER_SPEED;
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
		left_key(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_RIGHT))
		right_key(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_W))
		w_key(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_A))
		a_key(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_S))
		s_key(cub);
	if (mlx_is_key_down(cub->mlx, MLX_KEY_D))
		d_key(cub);
}