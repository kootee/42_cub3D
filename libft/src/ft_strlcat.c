/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:11:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:36 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int	i;
	size_t			dest_strlen;

	i = 0;
	dest_strlen = ft_strlen(dst);
	if (!dstsize || dest_strlen >= dstsize)
		return (ft_strlen(src) + dstsize);
	while (i < dstsize - dest_strlen - 1 && src[i])
	{
		dst[dest_strlen + i] = src[i];
		i++;
	}
	dst[dest_strlen + i] = 0;
	return (ft_strlen(dst) + ft_strlen(&src[i]));
}
