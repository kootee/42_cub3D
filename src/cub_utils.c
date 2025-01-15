/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 13:53:08 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/15 14:08:28 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

bool	is_texture_coordinate(char *str)
{
	return (strncmp(str, "NO ", 3) == 0
			|| strncmp(str, "SO ", 3) == 0
			||strncmp(str, "WE ", 3) == 0
			|| strncmp(str, "EA ", 3) == 0);
}

void    check_texture(char *path, t_cub *cub)
{
    if (!path)
		error_terminate_mlx(cub, ERROR_MALLOC_FAIL);
}