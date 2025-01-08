/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_validation.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psitkin <psitkin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 23:27:24 by psitkin           #+#    #+#             */
/*   Updated: 2025/01/07 23:27:25 by psitkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	validate_arguments(int argc, char **argv)
{
	size_t	len;
	int		fd;

	if (argc != 2)
		handle_error(ERROR_CMD_COUNT_ERROR);
	len = ft_strlen(argv[1]);
	if (len < 5 || ft_strncmp(argv[1] + len - 4, ".cub", 4) != 0)
		handle_error(ERROR_INVALID_FILE_NAME);
	if (ft_strncmp(argv[1], "maps/valid/", 11) != 0
		&& ft_strncmp(argv[1], "maps/unvalid/", 13) != 0)
		handle_error(ERROR_INVALID_FILE_NAME);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		handle_error(ERROR_OPEN_ERROR);
	close(fd);
	return (0);
}
