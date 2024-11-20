/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:34:19 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/20 19:27:42 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* 
	Allowed functions:
	open, close, read, write,
	printf, malloc, free, perror,
	strerror, exit, gettimeofday
	All functions of the math
	library (-lm man man 3 math) 	*/

# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include "MLX42.h"
# include "libft.h"

# define WIN_X	640
# define WIN_Y	480
# define WIN_MARGIN 50
# define NUM_TEXTURES 4
# define TEXTURE_X 64
# define TEXTURE_Y 64

# define BLACK		0x000000
# define WHITE		0xffffff
# define MAGENTA	0xff0099
# define LIGHTBLUE	0x87cefa
# define ORANGE		0xffc100
# define DARKORANGE	0xd75000
# define GREEN		0x00ff2e

# define PLAYER_SPEED 0.045
# define ROT_SPEED 4

typedef enum e_errorcode
{
	ERROR_CMD_COUNT_ERROR = 200,
	ERROR_MALLOC_FAIL = 201,
	ERROR_INVALID_MAP_PTS = 202,
	ERROR_INVALID_MAP_DIM = 203,
	ERROR_OPEN_ERROR = 204,
	ERROR_INVALID_FILE_NAME = 205,
	ERROR_INVALID_MAP = 206,
	ERROR_TEXTURE = 207
}	t_errorcode;

typedef enum e_cardinal_direction
{
	NORTH,
	SOUTH,
	WEST,
	EAST
} t_cardinal_direction;

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
} t_vector;

typedef struct s_coord
{
	int	x_coord;
	int	y_coord;
} t_coord;

typedef struct s_player 
{
	struct	s_vector	ppos;
	struct	s_vector	dir;
	double	p_angle;
	double	plane_x;	// player plane
	double	plane_y;
} t_player;

typedef	struct s_ray_data
{
	t_vector	d_dist;
    t_vector    step; // direction in which the ray moves
    t_vector    side_dist; //length of ray from current position to next x or y-side
	t_coord     map_coord;
	t_vector	dir;
    double  	wall_dist;
	double		wall_x;
	int     	side;
    int     	draw_start;
    int     	draw_end;
	int			line_height;
} t_ray_data;

typedef struct s_textures 
{
	mlx_texture_t	*north;
	mlx_texture_t	*south;
	mlx_texture_t	*east;
	mlx_texture_t	*west;
} t_textures;

typedef struct s_tex_data
{
	int			tex_x;
	int			tex_y;
	double		pos;
} t_tex_data;

typedef struct s_cub 
{
	mlx_t				*mlx;
	mlx_image_t			*mlx_img;
	mlx_texture_t		*texture_buff[NUM_TEXTURES]; // texture_buffer[n][y * 64 + x]
	struct s_textures	textures;
	struct s_tex_data	tex_data;
	struct s_player		player;
	struct s_ray_data	ray;
	t_vector      		camera_plane;
	char 				**map;
	int					**pixel_map;
	uint32_t			ceiling_color;
	uint32_t			floor_color;
} t_cub;

/* Initialise cube3D */
void	init_cub(t_cub *cub, char **argv, int argc);

/* Raycasting */
void    ray_cast(t_cub *cub);

/* Key actions */
void	ft_hook(void *param);

/* Draw functions */
void	draw_to_screen(t_cub * cub, t_ray_data *ray, int x_to_draw);
int		ft_putpixel(mlx_image_t *img, float x, float y, int32_t color);

/* Parse map */
void    parse_map(char *map_file_path);

/* Error handling */
void	handle_error(int errno);
void	error_terminate_mlx(t_cub *cub, int errno);

#endif