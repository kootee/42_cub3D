/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:42:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/25 17:37:53 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

mlx_texture_t	*set_texture(t_cub *cub)
{
	if (cub->ray.side == 0 && cub->ray.dir.x > 0)
		return (cub->textures.east);
	else if (cub->ray.side == 0)
		return (cub->textures.west);
	if (cub->ray.side == 1 && cub->ray.dir.y < 0)
		return (cub->textures.north);
	else
		return (cub->textures.south);
}

void	draw_floor_ceiling(t_cub *cub, t_ray_data *ray, int x_coord)
{
	int	y_coord;

	y_coord = 0;
	while (y_coord < ray->draw_start && y_coord < WIN_Y)
		ft_putpixel(cub->mlx_img, x_coord, y_coord++, cub->floor_color);
	y_coord = ray->draw_end;
	while (y_coord < WIN_Y)
		ft_putpixel(cub->mlx_img, x_coord, y_coord++, cub->ceiling_color);
}

// calculate x coordinate for texture
mlx_texture_t	*set_texture_data(t_cub *cub, double *step)
{
	mlx_texture_t	*texture;
	
	texture = set_texture(cub);
	*step = (double)(1.0 * texture->height / cub->ray.line_height);
	cub->tex_data.tex_x = (int)(cub->ray.wall_x * texture->width);
	if (cub->ray.side == 0 && cub->ray.dir.x < 0)
		cub->tex_data.tex_x = texture->width - cub->tex_data.tex_x - 1;
	if (cub->ray.side == 1 && cub->ray.dir.y > 0)
		cub->tex_data.tex_x = texture->width - cub->tex_data.tex_x - 1;

	cub->tex_data.pos = (cub->ray.draw_start - WIN_Y / \
						2 + cub->ray.line_height / 2) * (*step);
	return (texture);
}

/*	1.	The value of tex_y is calculated by increasing by a precomputed 
		step size (step). This is possible because this is constant in 
		the vertical stripe for each pixel. 
	2.	The step size tells how much to increase in the texture coordinates 
		(in floating point) for every pixel in vertical screen coordinates. 
	3.	It then casts the floating point value to integer to select 
		the actual texture pixel. */
void	draw_texture_column(t_cub *cub, t_ray_data *ray, int x)
{
	mlx_texture_t	*texture;
	uint8_t			*curr_pixel;
	double			step;
	int				y;

	texture = set_texture_data(cub, &step);
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		cub->tex_data.tex_y = (int)(cub->tex_data.pos) % texture->height;
		curr_pixel = texture->pixels + \
					((cub->tex_data.tex_y * texture->width * texture->bytes_per_pixel) + 
					(cub->tex_data.tex_x * texture->bytes_per_pixel));
		ft_putpixel(cub->mlx_img, x, y, get_pixel_color(curr_pixel));
		cub->tex_data.pos += step;
		y++;
	}
}

void	draw_to_screen(t_cub * cub, t_ray_data *ray, int x_to_draw)
{
	if (ray->draw_end > 0)
	{
		draw_floor_ceiling(cub, ray, x_to_draw);
		draw_texture_column(cub, ray, x_to_draw);
	}
}