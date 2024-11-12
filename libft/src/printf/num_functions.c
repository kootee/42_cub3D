/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   num_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:48:53 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:57:08 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../../include/libft.h"

int	check_length(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i = 1;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

int	putnbr(long n)
{
	char	c;
	int		return_len;

	return_len = check_length(n);
	if (n < 0)
	{
		if (0 > ft_putchar('-'))
			return (-1);
		n = n * -1;
	}
	if (n < 10)
	{
		c = n + '0';
		if (0 > ft_putchar(c))
			return (-1);
	}
	else
	{
		if (0 > putnbr(n / 10))
			return (-1);
		c = n % 10 + '0';
		if (0 > ft_putchar(c))
			return (-1);
	}
	return (return_len);
}
