/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:45:01 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/15 14:09:01 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_error(int errno)
{
	if (errno == ERROR_CMD_COUNT_ERROR)
		ft_putstr_fd("Error: Invalid number of arguments\n", STDERR_FILENO);
	else if (errno == ERROR_OPEN_ERROR || errno == ERROR_INVALID_FILE_NAME)
		ft_putstr_fd("Error: Invalid file\n", STDERR_FILENO);
	else if (errno == ERROR_INVALID_MAP)
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
	else if (errno == ERROR_INVALID_MAP_DIM)
		ft_putstr_fd("Error: Invalid map dimensions\n", STDERR_FILENO);
	else if (errno == ERROR_INVALID_MAP_PTS)
		ft_putstr_fd("Error: Invalid map points\n", STDERR_FILENO);
	else if (errno == ERROR_MALLOC_FAIL)
		ft_putstr_fd("Error: Malloc fail\n", STDERR_FILENO);
	else if (errno == ERROR_INVALID_FILE_NAME)
		ft_putstr_fd("Error: Invalid file name\n", STDERR_FILENO);
	else if (errno == ERROR_TEXTURE)
		ft_putstr_fd("Error: Failed to load texture\n", STDERR_FILENO);
	else if (errno == ERROR_INVALID_PLAYER_POSITION)
		ft_putstr_fd("Error: Invalid player position\n", STDERR_FILENO);
	else if (errno == ERROR_INVALID_RGB_VAL)
		ft_putstr_fd("Error: Invalid RGB value\n", STDERR_FILENO);
	exit (errno);
}

void	error_terminate_mlx(t_cub *cub, int errno)
{
	free_all_resources(cub);
	handle_error(errno);
}
