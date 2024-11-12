/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:34:19 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/12 20:55:43 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

/* • open, close, read, write,
	printf, malloc, free, perror,
	strerror, exit, gettimeofday
	• All functions of the math
	library (-lm man man 3 math) */

# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# include "MLX42.h"
# include "libft.h"

# define WIN_X	1080
# define WIN_Y	1080
# define WIN_MARGIN 50

typedef enum s_errorcode
{
	EXIT_CMD_COUNT_ERROR = 200,
	EXIT_MALLOC_FAIL = 201,
	EXIT_INVALID_MAP_PTS = 202,
	EXIT_INVALID_MAP_DIM = 203,
	EXIT_OPEN_ERROR = 204,
	EXIT_INVALID_FILE_NAME = 205,
	EXIT_INVALID_MAP = 206
}	t_errorcode;

typedef	struct s_map
{
	// map struct	
} t_map;

typedef struct s_vector
{
	double	x_dir;
	double	y_dir;
} t_vector;

typedef struct s_coord
{
	double	x_coord;
	double	y_coord;
} t_coord;

typedef struct s_player 
{
	struct s_coord	ppos;
	struct s_vector dir;
	double	plane_x;	// player plane
	double	plane_y;
} t_player;

typedef struct s_cub 
{
	mlx_t				*mlx;
	t_map				map;
	mlx_image_t			*img;
	
	struct s_player		*player;
} t_cub;

/* Functions */

/* Raycasting */
t_vector    ray_direction(t_player player);


#endif