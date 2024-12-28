/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:50:00 by ktoivola          #+#    #+#             */
/*   Updated: 2024/12/28 17:26:53 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	parse_colors(t_cub *cub, char **file_content);
uint32_t	parse_color(char *line);
char	*get_texture_path(char *line);
void parse_map(t_cub *cub, char *map_file);
size_t get_map_width(t_cub *cub);
void	validate_map(char **map, size_t map_height);
int		check_borders(char **map, size_t map_height);
int		check_valid_characters(char **map);
int		is_line_wall(char *line);

// void    parse_map(t_cub *cub, char *map_file_path)
// {
//     (void)cub; // Temp
//     if (map_file_path == NULL || *map_file_path == '\0')
//         return ;
//     // IMPLEMENT
// }






size_t get_map_width(t_cub *cub)
{
    size_t max_width = 0;
    for (size_t i = 0; i < cub->map_height; i++)
        max_width = fmax(max_width, ft_strlen(cub->map[i]));
    return max_width;
}

void parse_map(t_cub *cub, char *map_file)
{
    int fd = open(map_file, O_RDONLY);
    if (fd < 0)
        handle_error(ERROR_OPEN_ERROR);
	
    char *line;
    char **map_lines = malloc(sizeof(char *) * 1000);  // Assume a max of 1000 lines
    if (!map_lines)
        handle_error(ERROR_MALLOC_FAIL);

    size_t map_height = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (line[0] != '\0')
            map_lines[map_height++] = line;

        if (map_height >= 1000)
        {
            handle_error(ERROR_INVALID_MAP_DIM);
        }
    }
    close(fd);

    cub->map = map_lines;
    cub->map_height = map_height;
    cub->map_width = get_map_width(cub);
	validate_map(cub->map, cub->map_height);
}

char *trim_newline(char *line)
{
    size_t len;

    if (!line)
        return (NULL);

    len = ft_strlen(line);
    if (len > 0 && line[len - 1] == '\n') // Если последний символ - это '\n'
        line[len - 1] = '\0';            // Удаляем его, заменяя на null-терминатор

    return (line);
}
int is_line_wall(char *line)
{
    size_t i;

    if (!line)
    {
        printf("is_line_wall: NULL line received\n");
        return (0);
    }

    line = trim_newline(line); // Удаляем символ новой строки
    printf("is_line_wall: processing line: '%s'\n", line);

    i = 0;
    while (line[i])
    {
        if (!ft_strchr("01NSEW ", line[i])) // Допустимые символы карты
        {
            printf("is_line_wall: invalid character '%c' at index %zu\n", line[i], i);
            return (0); // Найден некорректный символ
        }
        i++;
    }
    return (1); // Линия валидна
}


int check_borders(char **map, size_t map_height)
{
    size_t i;

    // Проверяем верхнюю и нижнюю границы
    if (!is_line_wall(trim_newline(map[0])) || !is_line_wall(trim_newline(map[map_height - 1])))
        return (0);

    // Проверяем левую и правую границы для каждой строки
    i = 1;
    while (i < map_height - 1)
    {
        char *line = trim_newline(map[i]);
        size_t len = ft_strlen(line);

        // Линия должна начинаться и заканчиваться на '1'
        if (len == 0 || line[0] != '1' || line[len - 1] != '1')
            return (0);

        i++;
    }
    return (1);
}

int check_player_position(char **map)
{
    size_t i, j;
    int player_count = 0;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (ft_strchr("NSEW", map[i][j])) // Главный персонаж
                player_count++;
            j++;
        }
        i++;
    }

    if (player_count != 1) // Проверяем, что персонаж ровно один
    {
        printf("check_player_position: found %d players\n", player_count);
        return (0);
    }
    return (1);
}


int check_valid_characters(char **map)
{
    size_t i;
    size_t j;

    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!ft_strchr("01NSEW ", map[i][j]))
                return (0);
            j++;
        }
        i++;
    }
    return (1);
}

void validate_map(char **map, size_t map_height)
{
    size_t i;

    if (!map || map_height == 0)
        handle_error(ERROR_INVALID_MAP);

    i = 0;
    while (i < map_height)
    {
        map[i] = trim_newline(map[i]); // Удаляем символ новой строки
        if (!map[i] || ft_strlen(map[i]) == 0)
        {
            handle_error(ERROR_INVALID_MAP_DIM);
        }
        i++;
    }

    // Проверяем границы
    if (!check_borders(map, map_height))
        handle_error(ERROR_INVALID_MAP_PTS);

    // Проверяем допустимые символы
    if (!check_valid_characters(map))
        handle_error(ERROR_INVALID_MAP);

    // Проверяем позицию игрока
    if (!check_player_position(map))
        handle_error(ERROR_INVALID_PLAYER_POSITION);
}



