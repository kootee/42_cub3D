/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:32:43 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/21 13:48:51 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    left_key(t_cub *cub)
{
    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->player.dir.x;
    cub->player.dir.x = cub->player.dir.x * cos(ROT_SPEED)
                            - cub->player.dir.y *  sin(ROT_SPEED);
    cub->player.dir.y = old_dirX * sin(ROT_SPEED) + cub->player.dir.y
                            *cos(ROT_SPEED);
    old_planeX = cub->camera_plane.x;
    cub->camera_plane.x = cub->camera_plane.x * cos(ROT_SPEED) 
                            - cub->camera_plane.y * sin(ROT_SPEED);
    cub->camera_plane.y = old_planeX * sin(ROT_SPEED) 
                            + cub->camera_plane.y * cos(ROT_SPEED);
}

void    right_key(t_cub *cub)
{
    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->player.dir.x;
    cub->player.dir.x = cub->player.dir.x * cos(-ROT_SPEED)
                            - cub->player.dir.y *  sin(-ROT_SPEED);
    cub->player.dir.y = old_dirX * sin(-ROT_SPEED) + cub->player.dir.y
                            *cos(-ROT_SPEED);
    old_planeX = cub->camera_plane.x;
    cub->camera_plane.x = cub->camera_plane.x * cos(-ROT_SPEED) 
                            - cub->camera_plane.y * sin(-ROT_SPEED);
    cub->camera_plane.y = old_planeX * sin(-ROT_SPEED) 
                            + cub->camera_plane.y * cos(-ROT_SPEED);
}

void    w_key(t_cub *cub)
{
    double next_x;
    double next_y;
    
    next_x = (cub->player.ppos.x + cub->player.dir.x) * PLAYER_SPEED;
    next_y = (cub->player.ppos.y + cub->player.dir.y) * PLAYER_SPEED;
    if (cub->map[(int)round(next_x)][(int)round(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = next_x;
    if (cub->map[(int)round(cub->player.ppos.x)][(int)round(next_y)] == '0')
        cub->player.ppos.y = next_y;
}

void    s_key(t_cub *cub)
{
    double prev_x;
    double prev_y;
    
    prev_x = (cub->player.ppos.x - cub->player.dir.x) * PLAYER_SPEED;
    prev_y = (cub->player.ppos.y - cub->player.dir.y) * PLAYER_SPEED;
    if (cub->map[(int)round(prev_x)][(int)round(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = prev_x;
    if (cub->map[(int)round(cub->player.ppos.x)][(int)round(prev_y)] == '0')
        cub->player.ppos.y = prev_y;
}

void    a_key(t_cub *cub)
{
    double left_x;
    double left_y;
    
    left_x = (cub->player.ppos.x - cub->camera_plane.x) * PLAYER_SPEED;
    left_y = (cub->player.ppos.y - cub->camera_plane.y) * PLAYER_SPEED;
    if (cub->map[(int)round(left_x)][(int)round(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = left_x;
    if (cub->map[(int)round(cub->player.ppos.x)][(int)round(left_y)] == '0')
        cub->player.ppos.y = left_y;
}

void    d_key(t_cub *cub)
{
    double right_x;
    double right_y;
    
    right_x = (cub->player.ppos.x + cub->camera_plane.x) * PLAYER_SPEED;
    right_y = (cub->player.ppos.y + cub->camera_plane.y) * PLAYER_SPEED;
    if (cub->map[(int)round(right_x)][(int)round(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = right_x;
    if (cub->map[(int)round(cub->player.ppos.x)][(int)round(right_y)] == '0')
        cub->player.ppos.y = right_y;
}

void	ft_hook(void *param)
{
	t_cub	*cub;
	mlx_t	*mlx_inst;

	cub = param;
	mlx_inst = cub->mlx;
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