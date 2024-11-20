/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 18:42:07 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/20 18:30:57 by ktoivola         ###   ########.fr       */
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
void	set_texture_coords(t_cub *cub, mlx_texture_t *texture)
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
void	draw_texture_column(t_cub *cub, t_ray_data *ray, int x)
{
	mlx_texture_t	*texture;
	uint32_t		color;
	uint8_t			*curr_pixel;
	int				y;
	double			step;

	texture = set_texture(cub);
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
		ft_putpixel(cub->mlx_img, x, y, color);
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