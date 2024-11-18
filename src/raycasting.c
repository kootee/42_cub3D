/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:11:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 17:39:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* To find the first wall that a ray encounters on its way, 
you have to let it start at the player's position, 
and then all the time, check whether or not the ray is inside a wall. 
If it's inside a wall (hit), then the loop can stop, 
calculate the distance, and draw the wall with the correct height. */

/* Main structure for the raycasting */
void    ray_cast(t_cub *cub)
{
    int x;

    while(x < WIN_X) // calculate for each vertical line on the screen (along x axis)
    {
        ray_direction(cub, &cub->player, x);
        delta_distance(&cub->ray, &cub->player);
        step_distance(&cub->ray, &cub->player);
        digital_differential_analysis(cub, &cub->ray);
        wall_height(&cub->ray, &cub->player);
        draw_to_screen(cub, &cub->ray, x);
        x++;
    }
    // raycasting algorithm done
}

/* 1: calculate ray direction */
void    ray_direction(t_cub *cub, t_player *player, int x)
{
    // calculate ray position and direction
    cub->camera_plane.x_dir = 2 * x /(double)WIN_X - 1;
    cub->ray.x_dir = player->dir.x_dir + player->plane_x 
                    * cub->camera_plane.x_dir;
    cub->ray.y_dir = player->dir.y_dir + player->plane_y 
                    * cub->camera_plane.x_dir;
}

/* 2: calculate delta distance */
void    delta_distance(t_ray_data *ray, t_player *player)
{
    // map coords are the current square of the map the ray is in
    ray->map_coord.x_coord = (int)player->ppos.x_dir;
    ray->map_coord.y_coord = (int)player->ppos.y_dir;
    ray->d_dist.x_dir = fabs(1 / ray->x_dir);
    ray->d_dist.y_dir = fabs(1 / ray->y_dir);
}

/* 3: calculate step and initial side distance */
void    step_distance(t_ray_data *ray, t_player *player)
{
    if (ray->x_dir < 0)
    {
        ray->step.x_dir = - 1;
        ray->side_dist.x_dir = (player->ppos.x_dir - ray->map_coord.x_coord) 
        * ray->d_dist.x_dir;
    }
    else
    {
        ray->step.x_dir = 1;
        ray->side_dist.x_dir = (ray->map_coord.x_coord + 1.0 
        - player->ppos.x_dir) * ray->d_dist.x_dir;
    }
    if (ray->y_dir < 0)
    {
        ray->step.y_dir = -1;
        ray->side_dist.y_dir = (player->ppos.y_dir - 
        ray->map_coord.y_coord) * ray->d_dist.y_dir;
    }
    else
    {
        ray->step.y_dir = 1;
        ray->side_dist.y_dir = (ray->map_coord.y_coord + 1.0 
        - player->ppos.y_dir) * ray->d_dist.y_dir;   
    }
}

/* 4: DDA (digital differential analysis) -> calculate the side length
    Increments the ray with 1 square every time, until a wall is hit. */
void    digital_differential_analysis(t_cub *cub, t_ray_data *ray)
{
    while(true)
    {
        if (ray->side_dist.x_dir < ray->side_dist.y_dir)
        {
            ray->side_dist.x_dir += ray->d_dist.x_dir;
            ray->map_coord.x_coord += ray->step.x_dir;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y_dir += ray->d_dist.y_dir;
            ray->map_coord.y_coord += ray->step.y_dir;
            ray->side = 1;
        } if (cub->map[ray->map_coord.x_coord][ray->map_coord.y_coord] == '1') // a wall is hit
            break;
    }
}

/*  5: calculate wall height. Calculate the distance of the ray to the wall, 
    so that we can calculate how high the wall has to be drawn after this */
t_ray_data    wall_height(t_ray_data *ray, t_player *player)
{
    int line_height;

    if (ray->side == 0)
       ray->wall_dist = (ray->map_coord.x_coord - player->ppos.x_dir 
                        + (1 - ray->step.x_dir) / 2) / ray->x_dir;
    else
        ray->wall_dist = (ray->map_coord.y_coord - player->ppos.y_dir 
                        + (1 - ray->step.y_dir) / 2) / ray->y_dir;
    line_height = (int)(WIN_Y / ray->wall_dist);
    ray->draw_start = -line_height / 2 + WIN_Y / 2;
    if (ray->draw_start < 0)
        ray->draw_start  = 0;
    ray->draw_end = line_height  / 2 + WIN_Y / 2;
    if (ray->draw_end >= WIN_Y)
        ray->draw_end = WIN_Y - 1;
    if (ray->side == 0)
        ray->wall_x = player->ppos.y_dir + ray->wall_dist 
                                * ray->d_dist.y_dir;
    else
        ray->wall_x = player->ppos.x_dir + ray->wall_dist 
                                * ray->d_dist.x_dir;
    ray->wall_x -= floor(ray->wall_x);
}
