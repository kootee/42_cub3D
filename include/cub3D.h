/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:34:19 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/19 13:15:06 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include <stdio.h>
# include "MLX42.h"
# include "libft.h"

# define WIN_X	1080
# define WIN_Y	1080
# define WIN_MARGIN 50
# define NUM_TEXTURES 4
# define TEXTURE_X 64
# define TEXTURE_Y 64
# define MINIMAP_TILE_SIZE 15
# define MAX_FILE_SIZE 1048576
# define ALPHA 0xFF

# define BLACK		0x000000ff
# define WHITE		0xffffffff
# define MAGENTA	0xff0099ff
# define LIGHTBLUE	0x87cefaff
# define ORANGE		0xffc100ff
# define DARKORANGE	0xd75000ff
# define GREEN		0x00ff2eff
# define RED		0xFF0000ff

# define PLAYER_SPEED 0.065
# define ROT_SPEED 0.045

typedef enum e_errorcode
{
	ERROR_CMD_COUNT_ERROR = 200,
	ERROR_MALLOC_FAIL = 201,
	ERROR_INVALID_MAP_PTS = 202,
	ERROR_INVALID_MAP_DIM = 203,
	ERROR_OPEN_ERROR = 204,
	ERROR_INVALID_FILE_NAME = 205,
	ERROR_INVALID_MAP = 206,
	ERROR_TEXTURE = 207,
	ERROR_INVALID_PLAYER_POSITION = 208,
	ERROR_INVALID_RGB_VAL = 209,
	ERROR_INVALID_PLAYER = 210,
	ERROR_UNCLOSED_MAP = 211,
	ERROR_INVALID_FILE = 212
}	t_errorcode;

typedef enum s_rgb_values
{
	R,
	G,
	B,
	A
}	t_rgb_values;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_coord
{
	int	x_coord;
	int	y_coord;
}	t_coord;

/* plane_x and plane_y are the player plane vectors */
typedef struct s_player
{
	struct s_vector	ppos;
	struct s_vector	dir;
	double			p_angle;
	double			plane_x;
	double			plane_y;
}	t_player;

/*	step: direction in which the ray moves
	side_dist: length of ray from current position to next x or y-side */
typedef struct s_ray_data
{
	t_vector	d_dist;
	t_vector	step;
	t_vector	side_dist;
	t_coord		map_coord;
	t_vector	dir;
	double		wall_dist;
	double		wall_x;
	int			side;
	int			draw_start;
	int			draw_end;
	int			line_height;
}	t_ray_data;

typedef struct s_textures {
	char			*north_path;
	char			*south_path;
	char			*west_path;
	char			*east_path;
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*east;
}	t_textures;

typedef struct s_tex_data
{
	int			tex_x;
	int			tex_y;
	double		pos;
}	t_tex_data;

typedef struct s_cub
{
	mlx_t				*mlx;
	mlx_image_t			*mlx_img;
	char				**map;
	struct s_textures	textures;
	struct s_tex_data	tex_data;
	struct s_player		player;
	struct s_ray_data	ray;
	struct s_vector		camera_plane;
	size_t				map_height;
	size_t				map_width;
	uint32_t			ceiling_color;
	uint32_t			floor_color;
	char				**map_file_lines;
	int					colors_set;
}	t_cub;

/* Minimap */
void		draw_minimap(t_cub *cub);

/* Raycasting */
void		ray_cast(t_cub *cub);

/* Draw functions */
void		draw_to_screen(t_cub *cub, t_ray_data *ray, int x_to_draw);
int			ft_putpixel(mlx_image_t *img, float x, float y, int32_t color);
uint32_t	set_minimap_color(t_cub *cub, t_vector *pt);

/* Struct init*/
void		init_main_struct(t_cub *cub);
void		handle_arguments(int argc, char **argv);
void		create_file(t_cub *cub, const char *filename);
void		is_map_valid(t_cub *cub);
void		init_game(t_cub *cub);

/*Load textures */
void		load_textures(t_cub *cub);
void		free_textures(t_cub *cub);
void		free_texture_paths(t_textures *textures);

void		parse_textures(char *line, t_cub *cub);
void		free_array(char **array);
void		parse_cub_file(t_cub *cub, char **lines);
void		copy_map(char **lines, t_cub *cub);
void		free_all_resources(t_cub *cub);

int			check_valid_characters(char **map, int row, int col);
void		calculate_map_width(t_cub *cub);

/* Parse map */
int			validate_arguments(int argc, char **argv);
void		map_floodfill(t_cub *cub);

/* Key actions */
void		left_key(t_cub *cub);
void		right_key(t_cub *cub);
void		a_key(t_cub *cub);
void		s_key(t_cub *cub);
void		w_key(t_cub *cub);
void		d_key(t_cub *cub);
bool		is_not_wall(char c);

/* Error handling */
void		handle_error(int errno);
void		error_terminate_mlx(t_cub *cub, int errno);

/* Cub utils */
uint32_t	get_pixel_color(uint8_t *pixel_buffer);
bool		is_texture_coordinate(char *str);
void		check_texture(char *path, t_cub *cub);
void		skip_rgb_whitespace(char **strs);
int			is_valid_map_line(t_cub *cub, char *line);

#endif