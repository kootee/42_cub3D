/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 20:11:12 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/23 10:33:40 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* 1: calculate ray position, ray direction and delta distance */
void    ray_dir_delta_dist(t_cub *cub, t_player player, int x)
{
    cub->camera_plane.x = 2 * x /(double)WIN_X - 1;
    cub->ray.dir.x = player.dir.x + player.plane_x 
                    * cub->camera_plane.x;
    cub->ray.dir.y = player.dir.y + player.plane_y 
                    * cub->camera_plane.x;
    cub->ray.map_coord.x_coord = (int)player.ppos.x;
    cub->ray.map_coord.y_coord = (int)player.ppos.y;
    cub->ray.d_dist.x = fabs(1 / cub->ray.dir.x);
    cub->ray.d_dist.y = fabs(1 / cub->ray.dir.y);
}

/* 2: calculate step and initial side distance */
void    step_distance(t_ray_data *ray, t_player *player)
{
    if (ray->dir.x < 0)
    {
        ray->step.x = - 1;
        ray->side_dist.x = (player->ppos.x - ray->map_coord.x_coord) 
        * ray->d_dist.x;
    }
    else
    {
        ray->step.x = 1;
        ray->side_dist.x = (ray->map_coord.x_coord + 1.0 
        - player->ppos.x) * ray->d_dist.x;
    }
    if (ray->dir.y < 0)
    {
        ray->step.y = -1;
        ray->side_dist.y = (player->ppos.y - 
        ray->map_coord.y_coord) * ray->d_dist.y;
    }
    else
    {
        ray->step.y = 1;
        ray->side_dist.y = (ray->map_coord.y_coord + 1.0 
        - player->ppos.y) * ray->d_dist.y;   
    }
}

/* 3: DDA (digital differential analysis) -> calculate the side length
    Increments the ray with 1 square every time, until a wall is hit. */
void    digital_differential_analysis(t_cub *cub, t_ray_data *ray)
{
    while(true)
    {
        if (ray->side_dist.x < ray->side_dist.y)
        {
            ray->side_dist.x += ray->d_dist.x;
            ray->map_coord.x_coord += ray->step.x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist.y += ray->d_dist.y;
            ray->map_coord.y_coord += ray->step.y;
            ray->side = 1;
        } if (cub->map[ray->map_coord.x_coord][ray->map_coord.y_coord] == '1') // a wall is hit
            break;
    }
}

/*  4: calculate wall height. Calculate the distance of the ray to the wall, 
    so that we can calculate how high the wall has to be drawn after this 
    wall_x represents the position where the wall was hit (it's actually an y-coordinate 
    of the wall if side==1, but it's always the x-coordinate of the texture.) */
void    wall_height(t_ray_data *ray, t_player *player)
{
    if (ray->side == 0)
       ray->wall_dist = (ray->map_coord.x_coord - player->ppos.x 
                        + (1 - ray->step.x) / 2) / ray->dir.x;
    else
        ray->wall_dist = (ray->map_coord.y_coord - player->ppos.y 
                        + (1 - ray->step.y) / 2) / ray->dir.y;
    ray->line_height = (int)(WIN_Y / ray->wall_dist);
    ray->draw_start = -ray->line_height / 2 + WIN_Y / 2;
    if (ray->draw_start < 0)
        ray->draw_start  = 0;
    ray->draw_end = ray->line_height  / 2 + WIN_Y / 2;
    if (ray->draw_end >= WIN_Y)
        ray->draw_end = WIN_Y - 1;
    // calculate value of wall_x - position where the wall was hit
    if (ray->side == 0)
        ray->wall_x = player->ppos.y + ray->wall_dist * ray->d_dist.y;
    else
        ray->wall_x = player->ppos.x + ray->wall_dist * ray->d_dist.x;
    ray->wall_x -= floor(ray->wall_x);
}

/*  To find the first wall that a ray encounters on its way, 
    you have to let it start at the player's position, and then all the time, 
    check whether or not the ray has hit a wall. When a wall is encountered, 
    calculate the distance, and draw the wall with the correct height.  */
void    ray_cast(t_cub *cub)
{
    int x;

    x = 0;
    while(x < WIN_X) // calculate for each vertical column on the screen (along x axis)
    {
        ray_dir_delta_dist(cub, cub->player, x);
        step_distance(&cub->ray, &cub->player);
        digital_differential_analysis(cub, &cub->ray);
        wall_height(&cub->ray, &cub->player);
        draw_to_screen(cub, &cub->ray, x);
        x++;
    }
}