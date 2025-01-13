/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:26:02 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/13 16:58:14 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_minimap_square(t_cub *cub ,t_vector map_pt, size_t size, uint32_t color)
{
	for (size_t y = map_pt.y; y <= (map_pt.y + size); y++)
	{
		for (size_t x = map_pt.x; x <= (map_pt.x + size); x++)
		{
			if (y == (map_pt.y + size) || x == (map_pt.x + size) || \
				y == map_pt.y || x == map_pt.x)
				ft_putpixel(cub->mlx_img, x, y, BLACK);
			else	ft_putpixel(cub->mlx_img, x, y, color);
		}
	}
}

void draw_line(t_cub *cub, t_vector start, t_vector end, uint32_t color)
{
    int dx = fabs(end.x - start.x);
    int dy = fabs(end.y - start.y);
    int step_x = start.x < end.x ? 1 : -1;
    int step_y = start.y < end.y ? 1 : -1;
    int err = dx - dy;

    while (true)
    {
        ft_putpixel(cub->mlx_img, start.x, start.y, color);
        if (start.x == end.x && start.y == end.y)
            break;
        int e2 = err * 2;
        if (e2 > -dy)
        {
            err -= dy;
            start.x += step_x;
        }
        if (e2 < dx)
        {
            err += dx;
            start.y += step_y;
        }
    }
}

void draw_player(t_cub *cub)
{
    int player_x;
    int player_y; 
    int ray_end_x;
    int ray_end_y; 
	
	player_x = (int)(cub->player.ppos.x * MINIMAP_TILE_SIZE);
	player_y = (int)(cub->player.ppos.y * MINIMAP_TILE_SIZE);
    draw_minimap_square(cub, (t_vector){player_x - 10 / 2, \
										player_y - 10 / 2}, \
										10, GREEN);
    ray_end_x = player_x + (cub->player.dir.x * 10);
    ray_end_y = player_y + (cub->player.dir.y * 10);
    draw_line(cub, (t_vector){player_x, player_y}, (t_vector){ray_end_x, ray_end_y}, RED);
}

uint32_t	set_minimap_color(t_cub *cub, t_vector *pt)
{
	uint32_t	color;
	char		tile;
	int 		x;
	int 		y;

	x = pt->x;
	y = pt->y;
	color = WHITE;
	tile = cub->map[y][x];
	if (tile == '1')
		color = ORANGE;
	else if (tile == '0' || tile == 'N' || tile == 'S' || tile == 'W' || tile == 'E')
		color = DARKORANGE;
	return (color);
}

void	draw_minimap(t_cub *cub)
{
	t_vector	pt;
	t_vector	map_pt;
	uint32_t	color;
	
	for (pt.y = 0; pt.y < cub->map_height; pt.y++)
	{
		for (pt.x = 0; pt.x < cub->map_width; pt.x++)
		{
			map_pt.y = pt.y * MINIMAP_TILE_SIZE;
			map_pt.x = pt.x * MINIMAP_TILE_SIZE;
			color = set_minimap_color(cub, &pt);
			draw_minimap_square(cub, map_pt, MINIMAP_TILE_SIZE, color);
		}
	}
	draw_player(cub);
}