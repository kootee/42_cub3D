/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:23:21 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:59 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../../include/libft.h"

static int	read_args(va_list args, const char *str)
{
	int		temp;
	int		prnt_count;
	int		i;

	i = 0;
	prnt_count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			temp = read_format(str[i + 1], args);
			if (0 > temp)
				return (-1);
			prnt_count += temp;
			i++;
		}
		else
		{
			if (0 > ft_putchar(str[i]))
				return (-1);
			prnt_count++;
		}
		i++;
	}
	return (prnt_count);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		prnt_count;

	va_start(args, str);
	prnt_count = read_args(args, str);
	va_end(args);
	return (prnt_count);
}
