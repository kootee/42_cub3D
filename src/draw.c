/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:42:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/20 15:42:56 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


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

// choose texture
void	set_texture(t_cub *cub, mlx_texture_t *texture)
{
	if (cub->ray.side == 0 && cub->ray.dir.x > 0)
		texture = cub->textures.east;
	else if (cub->ray.side == 0)
		texture = cub->textures.west;
	else if (cub->ray.side == 1 && cub->ray.dir.y < 0)
		texture = cub->textures.north;
	else
		texture = cub->textures.south;
}

	// calculate x coordinate for texture
set_texture_coords(t_cub *cub, mlx_texture_t *texture)
{
	cub->tex_data.tex_x = (int)(cub->ray.wall_x * (double)texture->width);
	if (cub->ray.side == 0 && cub->ray.dir.x > 0)
		cub->tex_data.tex_x = texture->width - cub->tex_data.tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.dir.y < 0)
		cub->tex_data.tex_x = texture->width - cub->tex_data.tex_x - 1;
}

	/* The value of texY is calculated by increasing by a precomputed 
	step size (which is possible because this is constant in the vertical 
	stripe) for each pixel. 
	The step size tells how much to increase in the texture coordinates 
	(in floating point) for every pixel in vertical screen coordinates. 
	It then needs to cast the floating point value to integer to select 
	the actual texture pixel. */
void	draw_texture_column(t_cub *cub, t_ray_data *ray, int x_column)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	uint8_t			*curr_pixel;
	int				y;
	double			step;

	set_texture(cub, texture);
	set_texture_coords(cub, texture);
	step = 1.0 * texture->height / ray->line_height;
	y = ray->draw_start;
	cub->tex_data.pos = (ray->draw_start - WIN_Y / 2 + ray->line_height) * step;
	while (y < ray->draw_end)
	{
		cub->tex_data.tex_y = (int)(cub->tex_data.pos) % texture->height;
		curr_pixel = texture->pixels \
					+ (cub->tex_data.tex_y * texture->width) \
					+ (cub->tex_data.tex_x * texture->bytes_per_pixel);
		color = *(uint32_t*)curr_pixel;
		if (ray->side == 1)
			color = (color >> 1) & 8355711;
		ft_putpixel(cub->mlx_img, x_column, y, color);
		cub->tex_data.pos += step;
		y++;
	}
}

void	draw_to_screen(t_cub * cub, t_ray_data *ray, int x_to_draw)
{
	draw_texture_column(cub, ray, x_to_draw);
	draw_floor_ceiling(cub, ray, x_to_draw);
}