#include "cub3D.h"

void parse_texture(char *line, t_cub *cub)
{
    if (strncmp(line, "NO ", 3) == 0) // Путь к текстуре "North"
        cub->textures.north_path = ft_strdup(line + 3);
    else if (strncmp(line, "SO ", 3) == 0) // Путь к текстуре "South"
        cub->textures.south_path = ft_strdup(line + 3);
    else if (strncmp(line, "WE ", 3) == 0) // Путь к текстуре "West"
        cub->textures.west_path = ft_strdup(line + 3);
    else if (strncmp(line, "EA ", 3) == 0) // Путь к текстуре "East"
        cub->textures.east_path = ft_strdup(line + 3);
    else
        handle_error(ERROR_INVALID_FILE_NAME); // Некорректная строка
}

void copy_map(char **lines, t_cub *cub)
{
    int i = 0;

    while (lines[i])
        i++;
    cub->map_height = i;
    cub->map = malloc(sizeof(char *) * (i + 1));
    if (!cub->map)
    {
        fprintf(stderr, "Error\nFailed to allocate memory for map.\n");
        return;
    }
    i = 0;
    while (lines[i])
    {
        cub->map[i] = ft_strdup(lines[i]);
        i++;
    }
    cub->map[i] = NULL;
}

int parse_cub_file(t_cub *cub, char **lines)
{
    int i = 0;

    while (lines[i])
    {
        if (strncmp(lines[i], "NO ", 3) == 0 || strncmp(lines[i], "SO ", 3) == 0 ||
            strncmp(lines[i], "WE ", 3) == 0 || strncmp(lines[i], "EA ", 3) == 0)
        {
            parse_texture(lines[i], cub); // Парсим пути текстур
        }
        else if (lines[i][0] == '1') // Начало карты
        {
            copy_map(&lines[i], cub); // Копируем карту
            break;
        }
        else
        {
            handle_error(ERROR_INVALID_FILE_NAME);
        }
        i++;
    }

    return (0);
}


