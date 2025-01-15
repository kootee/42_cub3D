/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:34:01 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/15 15:13:04 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	check_file_format(const char *filename)
{
	if (strlen(filename) < 4 \
		|| strcmp(filename + strlen(filename) - 4, ".cub") != 0)
	{
		fprintf(stderr, "Error: Invalid file format\n");
		return (1);
	}
	return (0);
}

int	validate_arguments(int argc, char **argv)
{
	size_t	len;
	int		fd;

	if (argc != 2)
		handle_error(ERROR_CMD_COUNT_ERROR);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		handle_error(ERROR_INVALID_FILE_NAME);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		handle_error(ERROR_OPEN_ERROR);
	close(fd);
	return (0);
}

void	handle_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Error: Wrong number of arguments\n");
		handle_error(1);
	}
	if (check_file_format(argv[1]))
		handle_error(1);
}
