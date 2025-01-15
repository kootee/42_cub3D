/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:37:42 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/15 15:34:34 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static char	*read_file_contents(const char *filename)
{
	int		fd;
	char	*file_contents;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error: Failed to open file\n");
		return (NULL);
	}
	file_contents = ft_calloc(MAX_FILE_SIZE + 1, sizeof(char));
	if (!file_contents)
	{
		close(fd);
		fprintf(stderr, "Error: Memory allocation failed for file reading\n");
		return (NULL);
	}
	read(fd, file_contents, MAX_FILE_SIZE);
	close(fd);
	return (file_contents);
}

void	create_file(t_cub *cub, const char *filename)
{
	char	*file_contents;
	char	**lines;

	file_contents = read_file_contents(filename);
	if (!file_contents)
		handle_error(1);
	lines = ft_split(file_contents, '\n');
	free(file_contents);
	cub->map_file_lines = lines;
	if (!lines || parse_cub_file(cub, lines))
	{
		fprintf(stderr, "Error: Failed to parse .cub file\n");
		free_array(lines);
		handle_error(1);
	}
	free_array(lines);
}
