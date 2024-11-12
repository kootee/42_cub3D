/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_format.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:43:58 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:57:11 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../../include/libft.h"

int	read_format(char c, va_list args)
{
	if (c == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (c == 'p')
		return (puthexptr(va_arg(args, unsigned long)));
	if (c == 'd' || c == 'i')
		return (putnbr(va_arg(args, int)));
	if (c == 'u')
		return (putnbr(va_arg(args, unsigned int)));
	if (c == 'X' || c == 'x')
		return (puthex(va_arg(args, unsigned int), c));
	return (ft_putchar(c));
}
