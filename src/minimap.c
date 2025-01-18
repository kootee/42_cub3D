/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 14:26:02 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/15 16:34:45 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	draw_square(t_cub *cub, t_vector pt, size_t size, uint32_t color)
{
	int	y;
	int	x;

	y = pt.y;
	while (y <= (pt.y + size))
	{
		x = pt.x;
		while (x <= (pt.x + size))
		{
			if (y == (pt.y + size) || x == (pt.x + size) || \
				y == pt.y || x == pt.x)
				ft_putpixel(cub->mlx_img, x, y, BLACK);
			else
				ft_putpixel(cub->mlx_img, x, y, color);
			x++;
		}
		y++;
	}
}

static void	set_minimap_step(t_coord *step, t_vector start, t_vector end)
{
	if (start.x < end.x)
		step->x_coord = 1;
	else
		step->x_coord = -1;
	if (start.y < end.y)
		step->y_coord = 1;
	else
		step->y_coord = -1;
}

void	draw_line(t_cub *cub, t_vector start, t_vector end, uint32_t color)
{
	t_coord	err;
	t_coord	d;
	t_coord	step;

	d.x_coord = fabs(end.x - start.x);
	d.y_coord = fabs(end.y - start.y);
	err.x_coord = d.x_coord - d.y_coord;
	set_minimap_step(&step, start, end);
	while (true)
	{
		ft_putpixel(cub->mlx_img, start.x, start.y, color);
		if (start.x == end.x && start.y == end.y)
			break ;
		err.y_coord = err.x_coord * 2;
		if (err.y_coord > -d.y_coord)
		{
			err.x_coord -= d.y_coord;
			start.x += step.x_coord;
		}
		if (err.y_coord < d.x_coord)
		{
			err.x_coord += d.x_coord;
			start.y += step.y_coord;
		}
	}
}

void	draw_player(t_cub *cub)
{
	int	player_x;
	int	player_y;
	int	ray_end_x;
	int	ray_end_y;

	player_x = (int)(cub->player.ppos.x * MINIMAP_TILE_SIZE);
	player_y = (int)(cub->player.ppos.y * MINIMAP_TILE_SIZE);
	draw_square(cub, (t_vector){player_x - 10 / 2, player_y - 10 / 2}, \
				10, GREEN);
	ray_end_x = player_x + (cub->player.dir.x * 10);
	ray_end_y = player_y + (cub->player.dir.y * 10);
	draw_line(cub, (t_vector){player_x, player_y}, \
	(t_vector){ray_end_x, ray_end_y}, RED);
}

void	draw_minimap(t_cub *cub)
{
	t_vector	pt;
	t_vector	map_pt;
	uint32_t	color;

	pt.y = 0;
	while (pt.y < cub->map_height)
	{
		pt.x = 0;
		while (pt.x < cub->map_width)
		{
			map_pt.y = pt.y * MINIMAP_TILE_SIZE;
			map_pt.x = pt.x * MINIMAP_TILE_SIZE;
			color = set_minimap_color(cub, &pt);
			draw_square(cub, map_pt, MINIMAP_TILE_SIZE, color);
			pt.x++;
		}
		pt.y++;
	}
	draw_player(cub);
}
