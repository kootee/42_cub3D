/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 10:35:40 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:36 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*cpy;
	int		len;

	len = ft_strlen((char *)s1);
	cpy = malloc(len + 1);
	if (!cpy)
		return (0);
	while (*s1)
		*cpy++ = *s1++;
	*cpy = 0;
	return (cpy - len);
}
