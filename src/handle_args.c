/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:34:01 by ktoivola          #+#    #+#             */
/*   Updated: 2025/01/14 14:34:04 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* static int	check_valid_file_path(const char *filename)
{
	if (strncmp(filename, "maps/", 5) != 0)
	{
		fprintf(stderr, "Error\nInvalid file path. Must be in 'maps/' directory.\n");
		return (1);
	}
	return (0);
} */

static int	check_file_format(const char *filename)
{
	if (strlen(filename) < 4 || strcmp(filename + strlen(filename) - 4, ".cub") != 0)
	{
		fprintf(stderr, "Error\nInvalid file format. Expected '.cub' extension.\n");
		return (1);
	}
	return (0);
}

int	handle_arguments(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Error\nWrong number of arguments. Usage: ./cub3d <map_file>\n");
		return (1);
	}
	if (check_file_format(argv[1]))
		return (1);
	return (0);
}
