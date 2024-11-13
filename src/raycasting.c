/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:11:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/13 19:32:39 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    raycast(t_cub *cub, t_wall_data *wall, int *side)
{
    t_wall_data wall;
    t_coord     map_coord;
    t_vector    step; // direction in which the ray moves
    t_vector    side_dist; // initial distance for ray to travel
    
    ray_direction(cub, cub->player);
    delta_distance(cub, *(cub->player), map_coord);
    step_dist(cub, map_coord, &step, &side_dist);
    *side = ddiff_analysis(cub, side_dist, step, map_coord);
    *wall = wall_height(cub, side, map_coord, step);
}

// 1: calculate ray direction
void    ray_direction(t_cub *cub, t_player *player)
{
    double      camera_x;
    int         x;

    x = 0;
    while (x < WIN_X)
    {
        camera_x = 2 * x /(double)WIN_X - 1;
        cub->ray.x_dir = player->dir.x_dir + player->plane_x * camera_x;
        cub->ray.y_dir = player->dir.y_dir + player->plane_y * camera_x;

        // ...
    }
}

// 2: calculate delta distance
void    delta_distance(t_cub *cub, t_player player, t_coord map_coord)
{
    map_coord.x_coord = (int)cub->player->ppos.x_coord;
    map_coord.y_coord = (int)cub->player->ppos.y_coord;
    cub->d_dist.x_dir = fabs(1 / cub->ray.x_dir);
    cub->d_dist.y_dir = fabs(1 / cub->ray.y_dir);
}

// 3: calculate step and initial side distance
void    step_dist(t_cub *cub, t_coord map, t_vector *step, t_vector *side_dist)
{
    t_coord ppos;

    ppos = cub->player->ppos;
    if (cub->ray.x_dir < 0)
    {
        step->x_dir = - 1;
        side_dist->x_dir = (ppos.x_coord - map.x_coord) * cub->d_dist.x_dir;
    }
    else
    {
        step->x_dir = 1;
        side_dist->x_dir = (map.x_coord + 1.0 - ppos.x_coord) * cub->d_dist.x_dir;
    }
    if (cub->ray.y_dir < 0)
    {
        step->y_dir = -1;
        side_dist->y_dir = (ppos.y_coord - map.y_coord) * cub->d_dist.y_dir;
    }
    else
    {
        step->y_dir = 1;
        side_dist->y_dir = (map.y_coord + 1.0 - ppos.y_coord) * cub->d_dist.y_dir;   
    }
}

// 4: digital differential analysis
int    ddiff_analysis(t_cub *cub, t_vector side_dist, t_vector step, t_coord map)
{ // cub here, includes map and player
    int side;

    while(true)
    {
        if (side_dist.x_dir < side_dist.y_dir)
        {
            side_dist.x_dir += cub->d_dist.x_dir;
            map.x_coord += step.x_dir;
            side = 0;
        }
        else
        {
            side_dist.y_dir += cub->d_dist.y_dir;
            map.y_coord += step.y_dir;
            side = 1;
        }if (cub->map.data[map.x_coord][map.y_coord] == '1')
            break;
    }
    return (side);
}

// 5: calculate wall height
t_wall_data    wall_height(t_cub *cub, int side, t_coord map_coord, t_vector step)
{
    t_wall_data wall;
    
    if (side == 0)
        wall.wall_dist = (map_coord.x_coord - cub->player->ppos.x_coord 
                    + (1 - step.x_dir) / 2) / cub->ray.x_dir;
    else
        wall.wall_dist = (map_coord.y_coord - cub->player->ppos.y_coord 
                    + (1 - step.y_dir) / 2) / cub->ray.y_dir;
    wall.line_height = (int)(WIN_Y / wall.wall_dist);
    wall.draw_start = -wall.line_height / 2 + WIN_Y / 2;
    if (wall.draw_start < 0)
        wall.draw_start = 0;

    wall.draw_end = wall.line_height  / 2 + WIN_Y / 2;
    if (wall.draw_end >= WIN_Y)
        wall.draw_end = WIN_Y - 1;
    if (side == 0)
        wall.wall_pos.x_coord = cub->player->ppos.y_coord + wall.wall_dist 
                                * cub->d_dist.y_dir;
    else
        wall.wall_pos.x_coord = cub->player->ppos.x_coord + wall.wall_dist 
                                * cub->d_dist.x_dir;
    wall.wall_pos.x_coord -= floor(wall.wall_pos.x_coord);
    return (wall);
}
