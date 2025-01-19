/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:37:42 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/19 13:24:17 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*read_file_contents(const char *filename)
{
	int		fd;
	char	*file_contents;
	int		bytes_read;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		handle_error(ERROR_OPEN_ERROR);
	file_contents = ft_calloc(MAX_FILE_SIZE + 1, sizeof(char));
	if (!file_contents)
	{
		close(fd);
		handle_error(ERROR_MALLOC_FAIL);
	}
	bytes_read = read(fd, file_contents, MAX_FILE_SIZE);
	if (bytes_read == MAX_FILE_SIZE)
	{
		ft_putstr_fd("The file is too big\n", STDERR_FILENO);
		close(fd);
		handle_error(ERROR_INVALID_FILE);
	}
	close(fd);
	return (file_contents);
}

void	create_file(t_cub *cub, const char *filename)
{
	char	*file_contents;
	char	**lines;

	file_contents = read_file_contents(filename);
	if (!file_contents)
		handle_error(ERROR_OPEN_ERROR);
	lines = ft_split(file_contents, '\n');
	free(file_contents);
	if (!lines)
	{
		error_terminate_mlx(cub, ERROR_MALLOC_FAIL);
	}
	else
	{
		cub->map_file_lines = lines;
		parse_cub_file(cub, lines);
	}
}
