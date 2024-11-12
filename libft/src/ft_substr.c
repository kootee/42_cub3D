/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:01:16 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:35 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*substr;
	size_t			i;
	size_t			s_len;

	i = 0;
	s_len = ft_strlen(s);
	if (len == 0 || start > s_len || s_len == 0)
		return (ft_strdup(""));
	if ((s_len - start) < len)
		substr = malloc(sizeof(char) * (s_len - start + 1));
	else
		substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (0);
	while ((i < len && s[start + i]))
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = 0;
	return (substr);
}
