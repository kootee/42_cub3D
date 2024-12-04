#include "cub3D.h"

int	validate_arguments(int argc, char **argv)
{
	if (argc != 2)
		handle_error(ERROR_CMD_COUNT_ERROR);

	size_t len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		handle_error(ERROR_INVALID_FILE_NAME);

	if (ft_strncmp(argv[1], "maps/valid/", 11) != 0 && 
	    ft_strncmp(argv[1], "maps/unvalid/", 13) != 0)
		handle_error(ERROR_INVALID_FILE_NAME);

	int fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		handle_error(ERROR_OPEN_ERROR);
	close(fd);

	return (0);
}

