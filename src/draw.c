/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:42:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/13 20:03:50 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_to_screen(t_cub * cub)
{
	/* 	int		len;

	delta_v.axis[X] = end.axis[X] - start.axis[X];
	delta_v.axis[Y] = end.axis[Y] - start.axis[Y];
	line = sqrt((delta_v.axis[X] * delta_v.axis[X]) + \
		(delta_v.axis[Y] * delta_v.axis[Y]));
	len = line;
	delta_v.axis[X] /= line;
	delta_v.axis[Y] /= line;
	pixel.axis[X] = start.axis[X];
	pixel.axis[Y] = start.axis[Y];
	while (line > 0)
	{
		pixel.color = gradient(start.color, end.color, len, len - line);
		ft_putpixel(fdf->img, pixel.axis[X], pixel.axis[Y], pixel.color);
		pixel.axis[X] += delta_v.axis[X];
		pixel.axis[Y] += delta_v.axis[Y];
		line -= 1;
	} */
}

void    draw_map(t_cub *cub)
{
    t_wall_data wall;
	int			side;
    
    raycast(cub, wall, &side);
    draw_texture(cub, wall, side);
	draw_to_screen(cub);
}

int	ft_putpixel(mlx_image_t *img, float x, float y, int32_t color)
{
	int	pixel;
	int	alpha;

	alpha = 0xFF;
	if (x > WIN_X || y > WIN_X \
		|| x < 0 || y < 0)
		return (-1);
	pixel = ((int)y * WIN_X * 4) + ((int)x * 4);
	set_pixel_color(&img->pixels[pixel], color, alpha);
	return (0);
}


void	set_pixel_color(uint8_t *pixel_buffer, int color, int alpha)
{
	if (get_endian() == 0)
	{
		pixel_buffer[R] = color;
		pixel_buffer[G] = color >> 8;
		pixel_buffer[B] = color >> 16;
		pixel_buffer[A] = alpha;
	}
	else
	{
		pixel_buffer[R] = color >> 16;
		pixel_buffer[G] = color >> 8;
		pixel_buffer[B] = color;
		pixel_buffer[A] = alpha;
	}
}