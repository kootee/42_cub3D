/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:34:19 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/06 02:00:31 by psitkin          ###   ########.fr       */
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
# include <stdio.h>
# include "MLX42.h"
# include "libft.h"

# define WIN_X	480
# define WIN_Y	480
# define WIN_MARGIN 50
# define NUM_TEXTURES 4
# define TEXTURE_X 64
# define TEXTURE_Y 64
# define MINIMAP_TILE_SIZE 15
#define MAX_FILE_SIZE 1048576
//# define M_PI_2 1.5707963267948966 // π/2

# define BLACK		0x000000ff
# define WHITE		0xffffffff
# define MAGENTA	0xff0099ff
# define LIGHTBLUE	0x87cefaff
# define ORANGE		0xffc100ff
# define DARKORANGE	0xd75000ff
# define GREEN		0x00ff2eff
# define RED		0xFF0000ff

# define PLAYER_SPEED 0.045
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
	ERROR_INVALID_PLAYER_POSITION = 208
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

typedef struct s_textures {
    char *north_path;          // Путь к текстуре "North"
    char *south_path;          // Путь к текстуре "South"
    char *west_path;           // Путь к текстуре "West"
    char *east_path;           // Путь к текстуре "East"
    mlx_texture_t *north;      // Загруженная текстура "North"
    mlx_texture_t *south;      // Загруженная текстура "South"
    mlx_texture_t *west;       // Загруженная текстура "West"
    mlx_texture_t *east;       // Загруженная текстура "East"
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
	struct s_textures	textures;
	struct s_tex_data	tex_data;
	struct s_player		player;
	struct s_ray_data	ray;
	struct s_vector		camera_plane;
	char 				**map;
	size_t				map_height;
	size_t				map_width;
	uint32_t			ceiling_color;
	uint32_t			floor_color;
} t_cub;

/* Initialise game */
void	init_game(t_cub *cub); //, char **argv, int argc);

/* Minimap */
void	draw_minimap(t_cub *cub);

/* Raycasting */
void    ray_cast(t_cub *cub);

/* Draw functions */
void	draw_to_screen(t_cub * cub, t_ray_data *ray, int x_to_draw);
int		ft_putpixel(mlx_image_t *img, float x, float y, int32_t color);

/* Struct init*/

void	init_main_struct(t_cub *cub);
int	handle_arguments(int argc, char **argv);
int	create_file(t_cub *cub, const char *filename);
int	is_map_valid(t_cub *cub);
/*Load textures */
void load_textures(t_cub *cub);
void free_textures(t_cub *cub);
void free_texture_paths(t_textures *textures);
//void free_textures(t_cub *cub);
void parse_textures(char *line, t_cub *cub);
void parse_colors(char *line, uint32_t *color);
void free_array(char **array);
int parse_cub_file(t_cub *cub, char **lines);
void copy_map(char **lines, t_cub *cub);
void free_all_resources(t_cub *cub);

int check_valid_characters(char **map, int row, int col);
void calculate_map_width(t_cub *cub);
int count_players(char **map, int *player_count, int row, int col, t_cub *cub);




/* Parse map */
int validate_arguments(int argc, char **argv);
//void	validate_map_section(char **lines);
//void	init_cub_structure(t_cub *cub, char **file_content);
//void	parse_textures(t_cub *cub, char **file_content);
//char	*get_texture_path(char *line);
//void	parse_colors(t_cub *cub, char **file_content);
//void free_components(char **components);
//int count_components(char *line);

//uint32_t	parse_color(char *line);
void parse_map(t_cub *cub, char *map_file);
//size_t get_map_width(t_cub *cub);
void	validate_map(char **map, size_t map_height);
int		check_borders(char **map, size_t map_height);
int		is_line_wall(char *line);

/* Key actions */
void    left_key(t_cub *cub);
void    right_key(t_cub *cub);
void    a_key(t_cub *cub);
void    s_key(t_cub *cub);
void    w_key(t_cub *cub);
void    d_key(t_cub *cub);

/* Error handling */
void	handle_error(int errno);
void	error_terminate_mlx(t_cub *cub, int errno);

/* Draw utils */
uint32_t	get_pixel_color(uint8_t *pixel_buffer);

#endif