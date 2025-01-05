#include "cub3D.h"

static char	*read_file_contents(const char *filename)
{
	int		fd;
	char	*file_contents;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error\nFailed to open file");
		return (NULL);
	}
	file_contents = ft_calloc(MAX_FILE_SIZE + 1, sizeof(char));
	if (!file_contents)
	{
		close(fd);
		fprintf(stderr, "Error\nMemory allocation failed for file reading.\n");
		return (NULL);
	}
	read(fd, file_contents, MAX_FILE_SIZE);
	close(fd);
	return (file_contents);
}
#include <stdlib.h>

void free_array(char **array)
{
    int i = 0;

    if (!array) // Проверяем, что массив не NULL
        return;

    while (array[i]) // Освобождаем каждую строку в массиве
    {
        free(array[i]);
        i++;
    }

    free(array); // Освобождаем сам массив указателей
}

int create_file(t_cub *cub, const char *filename)
{
    char *file_contents = read_file_contents(filename);
    if (!file_contents)
        return (1);

    char **lines = ft_split(file_contents, '\n');
    free(file_contents);

    if (!lines || parse_cub_file(cub, lines))
    {
        fprintf(stderr, "Error\nFailed to parse .cub file.\n");
        free_array(lines);
        return (1);
    }

    free_array(lines);
    return (0);
}
