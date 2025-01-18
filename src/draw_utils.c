/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 15:47:41 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/18 16:34:40 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_endian(void)
{
	int		endian;
	int16_t	x;

	x = 0x0001;
	endian = (*((int8_t *)(&x)) == 0x01);
	return (endian);
}

uint32_t	get_pixel_color(uint8_t *pixel_buffer)
{
	uint32_t	color;

	if (get_endian() == 0)
	{
		color = (pixel_buffer[A] << 24) | \
				(pixel_buffer[B] << 16) | \
				(pixel_buffer[G] << 8) | \
				pixel_buffer[R];
	}
	else
	{
		color = (pixel_buffer[R] << 24) | \
				(pixel_buffer[G] << 16) | \
				(pixel_buffer[B] << 8) | \
				pixel_buffer[A];
	}
	return (color);
}

void	set_pixel_color(uint8_t *pixel_buffer, int color, int alpha)
{
	if (get_endian() == 0)
	{
		pixel_buffer[R] = color >> 8;
		pixel_buffer[G] = color >> 16;
		pixel_buffer[B] = color >> 24;
		pixel_buffer[A] = alpha;
	}
	else
	{
		pixel_buffer[R] = color >> 24;
		pixel_buffer[G] = color >> 16;
		pixel_buffer[B] = color >> 8;
		pixel_buffer[A] = alpha;
	}
}

int	ft_putpixel(mlx_image_t *img, float x, float y, int32_t color)
{
	int	pixel;
	int	alpha;

	alpha = ALPHA;
	if (x > WIN_X || y > WIN_X \
		|| x < 0 || y < 0)
		return (-1);
	pixel = ((int)y * WIN_X * 4) + ((int)x * 4);
	set_pixel_color(&img->pixels[pixel], color, alpha);
	return (0);
}

uint32_t	set_minimap_color(t_cub *cub, t_vector *pt)
{
	uint32_t	color;
	int			x;
	int			y;

	x = pt->x;
	y = pt->y;
	color = DARKORANGE;
	if (cub->map[y][x] == '1')
		color = ORANGE;
	else if (cub->map[y][x] == '0' \
			|| cub->map[y][x] == 'N' \
			|| cub->map[y][x] == 'W' \
			|| cub->map[y][x] == 'S' \
			|| cub->map[y][x] == 'E')
		color = DARKORANGE;
	return (color);
}
