/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:45:01 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/18 17:00:41 by ktoivola         ###   ########.fr       */
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
    // free allocated memory
	exit (errno);
}

void	error_terminate_mlx(t_cub *cub, int errno)
{
	mlx_terminate(cub->mlx);
	handle_error(errno);
}