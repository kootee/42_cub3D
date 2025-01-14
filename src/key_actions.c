/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:32:43 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/14 14:43:54 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_not_wall(char c)
{
	return (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E');
}

void	right_key(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cos(ROT_SPEED) \
						- cub->player.dir.y * sin(ROT_SPEED);
	cub->player.dir.y = old_dir_x * sin(ROT_SPEED) + cub->player.dir.y \
						*cos(ROT_SPEED);
	old_plane_x = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(ROT_SPEED) \
						- cub->player.plane_y * sin(ROT_SPEED);
	cub->player.plane_y = old_plane_x * sin(ROT_SPEED) \
						+ cub->player.plane_y * cos(ROT_SPEED);
}

void	left_key(t_cub *cub)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = cub->player.dir.x;
	cub->player.dir.x = cub->player.dir.x * cos(-ROT_SPEED) \
						- cub->player.dir.y * sin(-ROT_SPEED);
	cub->player.dir.y = old_dir_x * sin(-ROT_SPEED) + cub->player.dir.y \
						*cos(-ROT_SPEED);
	old_plane_x = cub->player.plane_x;
	cub->player.plane_x = cub->player.plane_x * cos(-ROT_SPEED) \
						- cub->player.plane_y * sin(-ROT_SPEED);
	cub->player.plane_y = old_plane_x * sin(-ROT_SPEED) \
						+ cub->player.plane_y * cos(-ROT_SPEED);
}
