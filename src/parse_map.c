/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 18:50:00 by ktoivola          #+#    #+#             */
/*   Updated: 2024/12/11 17:16:47 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**read_cub_file(const char *filepath);
void	validate_map_section(char **lines);
void	init_cub_structure(t_cub *cub, char **file_content);
void	parse_textures(t_cub *cub, char **file_content);
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

char	**read_cub_file(const char *filepath)
{
	int		fd;
	char	*line;
	char	**lines;
	int		line_count = 0;

	fd = open(filepath, O_RDONLY);
	if (fd == -1)
		handle_error(ERROR_OPEN_ERROR);

	lines = ft_calloc(1024, sizeof(char *)); // Массив для строк
	if (!lines)
		handle_error(ERROR_MALLOC_FAIL);

	while ((line = get_next_line(fd)) != NULL)
	{
		lines[line_count++] = line; // Сохраняем каждую строку
		if (line_count >= 1024) // Проверяем переполнение
			handle_error(ERROR_INVALID_MAP_DIM);
	}
	close(fd);
	return (lines); // Возвращаем массив строк
}

void	validate_map_section(char **lines)
{
	int i = 0;

	while (lines[i])
	{
		// Пропускаем пустые строки
		if (ft_strlen(lines[i]) == 0)
		{
			i++;
			continue;
		}

		// Проверяем первую букву строки
		if (ft_strncmp(lines[i], "NO ", 3) == 0 ||
			ft_strncmp(lines[i], "SO ", 3) == 0 ||
			ft_strncmp(lines[i], "WE ", 3) == 0 ||
			ft_strncmp(lines[i], "EA ", 3) == 0)
		{
			// Проверка текстур...
		}
		else if (lines[i][0] == 'F' || lines[i][0] == 'C')
		{
			// Проверка цветов...
		}
		else
		{
			// Проверка карты...
		}
		i++;
	}
}

void	init_cub_structure(t_cub *cub, char **file_content)
{
	ft_bzero(cub, sizeof(t_cub)); // Обнуляем все поля структуры

	// Инициализируем MLX
	cub->mlx = mlx_init(WIN_X, WIN_Y, "Cub3D", true);
	if (!cub->mlx)
		handle_error(ERROR_MALLOC_FAIL);

	// Парсим текстуры
	parse_textures(cub, file_content);

	// Парсим цвета
	parse_colors(cub, file_content);

	// Парсим карту
	parse_map(cub, *file_content);
}
void	parse_textures(t_cub *cub, char **file_content)
{
	int i = 0;

	while (file_content[i])
	{
		if (ft_strncmp(file_content[i], "NO ", 3) == 0)
			cub->textures.north = mlx_load_png(get_texture_path(file_content[i]));
		else if (ft_strncmp(file_content[i], "SO ", 3) == 0)
			cub->textures.south = mlx_load_png(get_texture_path(file_content[i]));
		else if (ft_strncmp(file_content[i], "WE ", 3) == 0)
			cub->textures.west = mlx_load_png(get_texture_path(file_content[i]));
		else if (ft_strncmp(file_content[i], "EA ", 3) == 0)
			cub->textures.east = mlx_load_png(get_texture_path(file_content[i]));
		i++;
	}

	// Проверяем, что все текстуры загружены
	if (!cub->textures.north || !cub->textures.south ||
		!cub->textures.west || !cub->textures.east)
		handle_error(ERROR_TEXTURE);
}

// Вспомогательная функция для получения пути к текстуре
char	*get_texture_path(char *line)
{
	char	*path;

	// Пропускаем ключевое слово (например, "NO ")
	path = ft_strchr(line, ' ') + 1;
	if (!path || ft_strlen(path) == 0)
		handle_error(ERROR_TEXTURE);
	return (ft_strdup(path));
}

void	parse_colors(t_cub *cub, char **file_content)
{
	int i = 0;

	while (file_content[i])
	{
		if (file_content[i][0] == 'F') // Пол
			cub->floor_color = parse_color(file_content[i] + 2);
		else if (file_content[i][0] == 'C') // Потолок
			cub->ceiling_color = parse_color(file_content[i] + 2);
		i++;
	}
}

void free_components(char **components)
{
    size_t i = 0;
    while (components[i])
    {
        free(components[i]); // Free each string in the array
        i++;
    }
    free(components); // Free the array itself
}

int count_components(char *line)
{
    int count = 1; // Start with 1 as the first component exists before the first comma
    while (*line)
    {
        if (*line == ',')
            count++;
        line++;
    }
    return count;
}

// Функция для парсинга RGB-цвета
uint32_t	parse_color(char *line)
{
	int		rgb[3];
	char	**components;

	components = ft_split(line, ',');
	if (!components || count_components(*components) != 3)
		handle_error(ERROR_INVALID_MAP_PTS);

	// Преобразуем компоненты цвета и проверяем диапазон
	rgb[0] = ft_atoi(components[0]); // R
	if (rgb[0] < 0 || rgb[0] > 255)
		handle_error(ERROR_INVALID_MAP_PTS);

	rgb[1] = ft_atoi(components[1]); // G
	if (rgb[1] < 0 || rgb[1] > 255)
		handle_error(ERROR_INVALID_MAP_PTS);

	rgb[2] = ft_atoi(components[2]); // B
	if (rgb[2] < 0 || rgb[2] > 255)
		handle_error(ERROR_INVALID_MAP_PTS);

	// Освобождаем память
	free_components(components);

	// Формируем 32-битный цвет
	return (rgb[0] << 24 | rgb[1] << 16 | rgb[2] << 8 | 0xFF);
}

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
            handle_error(ERROR_INVALID_MAP_DIM);
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
            handle_error(ERROR_INVALID_MAP_DIM);
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



