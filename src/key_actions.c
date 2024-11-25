/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 15:32:43 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/25 15:58:16 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>

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

void    w_key(t_cub *cub)
{
    printf("w key pressed\n");

    double next_x;
    double next_y;
    
    next_x = cub->player.ppos.x + cub->player.dir.x * PLAYER_SPEED;
    next_y = cub->player.ppos.y + cub->player.dir.y * PLAYER_SPEED;
    
    printf("Next position: (%f, %f)\n", next_x, next_y);
    printf("Map value at next_x: %c\n", cub->map[(int)next_x][(int)cub->player.ppos.y]);
    printf("Map value at next_y: %c\n", cub->map[(int)cub->player.ppos.x][(int)next_y]);

    if (cub->map[(int)(next_x)][(int)(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = next_x;
    if (cub->map[(int)(cub->player.ppos.x)][(int)(next_y)] == '0')
        cub->player.ppos.y = next_y;

    printf("Updated position: (%f, %f)\n", cub->player.ppos.x, cub->player.ppos.y);

}

void    s_key(t_cub *cub)
{
    printf("s key pressed\n");

    double prev_x;
    double prev_y;
    
    prev_x = cub->player.ppos.x - cub->player.dir.x * PLAYER_SPEED;
    prev_y = cub->player.ppos.y - cub->player.dir.y * PLAYER_SPEED;
    if (cub->map[(int)(prev_x)][(int)(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = prev_x;
    if (cub->map[(int)(cub->player.ppos.x)][(int)(prev_y)] == '0')
        cub->player.ppos.y = prev_y;
}

void    a_key(t_cub *cub)
{
    printf("a key pressed\n");

    double left_x;
    double left_y;
    
    left_x = cub->player.ppos.x - cub->player.plane_x * PLAYER_SPEED;
    left_y = cub->player.ppos.y - cub->player.plane_y * PLAYER_SPEED;
    if (cub->map[(int)(left_x)][(int)(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = left_x;
    if (cub->map[(int)(cub->player.ppos.x)][(int)(left_y)] == '0')
        cub->player.ppos.y = left_y;
}

void    d_key(t_cub *cub)
{
    printf("d key pressed\n");

    double right_x;
    double right_y;
    
    right_x = cub->player.ppos.x + cub->player.plane_x * PLAYER_SPEED;
    right_y = cub->player.ppos.y + cub->player.plane_y * PLAYER_SPEED;
    if (cub->map[(int)(right_x)][(int)(cub->player.ppos.y)] == '0')
        cub->player.ppos.x = right_x;
    if (cub->map[(int)(cub->player.ppos.x)][(int)(right_y)] == '0')
        cub->player.ppos.y = right_y;
}
