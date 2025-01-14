/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_and_read.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:37:42 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/14 15:45:31 by psitkin          ###   ########.fr       */
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

int	create_file(t_cub *cub, const char *filename)
{
	char	*file_contents;
	char	**lines;

	file_contents = read_file_contents(filename);
	if (!file_contents)
		return (1);
	lines = ft_split(file_contents, '\n');
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
