/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:11:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/12 21:06:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// 1: calculate ray direction
// determine angle of the ray relative
// to players view and converting it into a unit vector
t_vector    ray_direction(t_player player)
{
    t_vector    ray_dir;
    double      camera_x;
    int x;

    x = 0;
    while (x < WIN_X)
    {
        camera_x = 2 * x /(double)WIN_X - 1;
        ray_dir.x_dir = player.dir.x_dir + player.plane_x * camera_x;
        ray_dir.y_dir = player.dir.y_dir + player.plane_y * camera_x;

        // ...
    }
}

// 2: calculate delta distance
// delta distance between two consecutive x or y intersections with
// a grid line. Determine the distance the ray must travel to
// the next grid line in the x or y direction

t_vector    delta_distance(t_player player)
{
    t_vector    ray;
    t_vector    ddist;
    t_vector    side_dist;
    t_coord     map_coord;
    
    ray = ray_direction(player);
    map_coord.x_coord = (int)player.ppos.x_coord;
    map_coord.y_coord = (int)player.ppos.y_coord;

    ddist.x_dir = fabs(1 / ray.x_dir);
    ddist.y_dir = fabs(1 / ray.y_dir);
    
    side_dist = step_dist(ray, player.ppos, map_coord, ddist);
}

// 3: calculate step and initial side distance
t_vector    step_dist(t_vector ray, t_coord ppos, t_coord map, t_vector ddist)
{
    t_vector    step; // direction in which the day moves
    t_vector    side_dist; // initial distance for ray to travel

    if (ray.x_dir < 0)
    {
        step.x_dir = - 1;
        side_dist.x_dir = (ppos.x_coord - map.x_coord) * ddist.x_dir;
    }
    else
    {
        step.x_dir = 1;
        side_dist.x_dir = (map.x_coord + 1.0 - ppos.x_coord) * ddist.x_dir;
    }
    if (ray.y_dir < 0)
    {
        step.y_dir = -1;
        side_dist.y_dir = (ppos.y_coord - map.y_coord) * ddist.y_dir;
    }
    else
    {
        step.y_dir = 1;
        side_dist.y_dir = (map.y_coord + 1.0 - ppos.y_coord) * ddist.y_dir;   
    }
    ddiff_analysis(side_dist, ddist, step, map);
}

// 4: digital differential analysis

void    ddiff_analysis(t_vector side_dist, t_vector ddist, t_vector step, t_coord map)
{
    int side;

    while(true)
    {
        if (side_dist.x_dir < side_dist.y_dir)
        {
            side_dist.x_dir += ddist.x_dir;
            map.x_coord += step.x_dir;
            side = 0;
        }
        else
        {
            side_dist.y_dir += ddist.y_dir;
            map.y_coord += step.y_dir;
            side = 1;
        }
    }   
}
