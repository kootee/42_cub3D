/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_functions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 10:46:14 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:57:05 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"
#include "../../include/libft.h"

static int	check_hexlength(unsigned long n)
{
	int	i;

	i = 0;
	if (!n)
		i = 1;
	if (n < 0)
		i++;
	while (n)
	{
		n /= 16;
		i++;
	}
	return (i);
}

static int	put_hexletters(unsigned long n, char format)
{
	if (format == 'x')
		return (ft_putchar(n - 10 + 'a'));
	if (format == 'X')
		return (ft_putchar(n - 10 + 'A'));
	return (0);
}

int	puthexptr(unsigned long address)
{
	int	len;

	if (0 > write(1, "0x", 2))
		return (-1);
	len = puthex(address, 'x');
	if (0 > len)
		return (-1);
	return (len + 2);
}

int	puthex(unsigned long n, char format)
{
	int	len;

	len = check_hexlength(n);
	if (n == 0)
		return (ft_putchar('0'));
	if (n >= 16)
	{
		if (0 > puthex(n / 16, format))
			return (-1);
		n = n % 16;
	}
	if (n <= 9)
	{
		if (0 > ft_putchar(n + '0'))
			return (-1);
	}
	else
	{
		if (0 > put_hexletters(n, format))
			return (-1);
	}
	return (len);
}
