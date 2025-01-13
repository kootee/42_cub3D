/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:32:43 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/13 16:47:44 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool    is_not_wall(char c)
{
    printf("checking %c \n", c);
    if (c == '0' || c == 'N' || c == 'W' || c == 'S' || c == 'E')
    {
        printf("returning true\n");
        return (true);
    }
    printf("returning false\n");
    return (false);
}

void    right_key(t_cub *cub)
{
    printf("right key pressed\n");
    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->player.dir.x;
    cub->player.dir.x = cub->player.dir.x * cos(ROT_SPEED)
                            - cub->player.dir.y * sin(ROT_SPEED);
    cub->player.dir.y = old_dirX * sin(ROT_SPEED) + cub->player.dir.y
                            *cos(ROT_SPEED);
    old_planeX = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(ROT_SPEED) 
                            - cub->player.plane_y * sin(ROT_SPEED);
    cub->player.plane_y = old_planeX * sin(ROT_SPEED) 
                            + cub->player.plane_y * cos(ROT_SPEED);
}

void    left_key(t_cub *cub)
{
    printf("left key pressed\n");

    double  old_dirX;
    double  old_planeX;
    
    old_dirX = cub->player.dir.x;
    cub->player.dir.x = cub->player.dir.x * cos(-ROT_SPEED)
                            - cub->player.dir.y * sin(-ROT_SPEED);
    cub->player.dir.y = old_dirX * sin(-ROT_SPEED) + cub->player.dir.y
                            *cos(-ROT_SPEED);
    old_planeX = cub->player.plane_x;
    cub->player.plane_x = cub->player.plane_x * cos(-ROT_SPEED) 
                            - cub->player.plane_y * sin(-ROT_SPEED);
    cub->player.plane_y = old_planeX * sin(-ROT_SPEED) 
                            + cub->player.plane_y * cos(-ROT_SPEED);
}