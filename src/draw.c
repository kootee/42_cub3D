/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:42:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 17:41:06 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	draw_to_screen(t_cub * cub, t_ray_data *ray, int x_to_draw)
{
	draw_texture_column(cub, ray, x_to_draw);
	draw_floor_ceiling(cub, ray, x_to_draw);
}

void	draw_texture_column(t_cub *cub, t_ray_data *ray, int x_to_draw)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	uint8_t			*pix;
	int				y_pos;

	/*
		calculate texture coordinate
		x coordinate on the texture
      	int texX = int(wallX * double(texWidth));
      	if(side == 0 && rayDirX > 0) texX = texWidth - texX - 1;
      	if(side == 1 && rayDirY < 0) texX = texWidth - texX - 1; 
	*/
	// set E W N S texture
	// modify alpha channel (divide channels by 2) to make walls on north face be darker?
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