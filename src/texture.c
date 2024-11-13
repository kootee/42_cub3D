/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:38:42 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/13 19:43:02 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_cardinal_direction    get_dir(t_vector ray)
{
    if (fabs(ray.x_dir) > fabs(ray.y_dir))
    {
        if (ray.x_dir > 0)
            return (EAST);
        else
            return (WEST);
    }
    else
    {
        if (ray.y_dir > 0)
            return (SOUTH);
        else
            return (NORTH);        
    }
}

void    draw_texture(t_cub *cub, t_wall_data wall, int side)
{
    t_cardinal_direction    dir;
    int                     texture_x;
    int                     colour;
    double                  pos;
    double                  step;

    dir = get_dir(cub->ray);
    texture_x = (int)(wall.wall_pos.x_coord * TEXTURE_SIZE);
    if (side == 0 && cub->ray.x_dir < 0 || (side == 1 && cub->ray.y_dir > 0))
        texture_x = TEXTURE_SIZE - texture_x - 1;
    step = 1.0 * TEXTURE_SIZE / wall.line_height;
    pos = (wall.draw_start - WIN_Y / 2 + wall.line_height / 2) * step;
    while (wall.draw_start < wall.draw_end)
    {
        pos += step;
        colour = cub->texture_buff[dir][TEXTURE_SIZE * 
                ((int)pos & (TEXTURE_SIZE -1)) + texture_x];
        if (dir == NORTH || dir == SOUTH)
            colour = (colour >> 1) & 0x7F7F7F;
        if (colour > 0)
            cub->pixel_map[wall.draw_start][x] = colour;
        wall.draw_start++;
    }
}