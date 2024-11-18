/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:34:19 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 15:54:21 by ktoivola         ###   ########.fr       */
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
# define TEXTURE_SIZE 64

# define PLAYER_SPEED 0.045
# define ROT_SPEED 4

typedef enum e_errorcode
{
	EXIT_CMD_COUNT_ERROR = 200,
	EXIT_MALLOC_FAIL = 201,
	EXIT_INVALID_MAP_PTS = 202,
	EXIT_INVALID_MAP_DIM = 203,
	EXIT_OPEN_ERROR = 204,
	EXIT_INVALID_FILE_NAME = 205,
	EXIT_INVALID_MAP = 206
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
	double	x_dir;
	double	y_dir;
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
	t_coord 	wall_pos;
	t_coord     map_coord;
	double		x_dir; // replace with vector
	double		y_dir; // replace with vector
    double  	wall_dist;
	int     	side;
    int     	draw_start;
    int     	draw_end;
} t_ray_data;

typedef struct s_cub 
{
	mlx_t				*mlx;
	mlx_image_t			*mlx_img;
	mlx_texture_t		*texture_buff[NUM_TEXTURES]; // texture_buffer[n][y * 64 + x]
	struct s_player		player;
	struct s_ray_data	ray;
	t_vector      		camera_plane;
	char 				**map;
	int					**pixel_map;
} t_cub;

/* Functions */
void	init_cub(t_cub *cub, char **argv, int argc);

/* Raycasting */
void    ray_cast(t_cub *cub);

/* Key actions */
static void	ft_hook(void *param);

#endif