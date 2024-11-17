/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 19:45:01 by ktoivola          #+#    #+#             */
/*   Updated: 2024/11/17 19:35:06 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	handle_error(t_cub *cub, int errno)
{
	if (errno == EXIT_CMD_COUNT_ERROR)
		ft_putstr_fd("Error: Invalid number of arguments\n", STDERR_FILENO);
	else if (errno == EXIT_OPEN_ERROR || errno == EXIT_INVALID_FILE_NAME)
		ft_putstr_fd("Error: Invalid file\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_MAP)
		ft_putstr_fd("Error: Invalid map\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_MAP_DIM)
		ft_putstr_fd("Error: Invalid map dimensions\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_MAP_PTS)
		ft_putstr_fd("Error: Invalid map points\n", STDERR_FILENO);
	else if (errno == EXIT_MALLOC_FAIL)
		ft_putstr_fd("Error: Malloc fail\n", STDERR_FILENO);
	else if (errno == EXIT_INVALID_FILE_NAME)
		ft_putstr_fd("Error: Invalid file name\n", STDERR_FILENO);
    // free allocated memory
	exit (errno);
}

void	error_terminate_mlx(t_cub *cub, int errno)
{
	mlx_terminate(cub->mlx);
	handle_error(&cub->map, errno);
}