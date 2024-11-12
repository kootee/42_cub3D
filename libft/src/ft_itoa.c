/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktoivola <ktoivola@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 14:36:46 by ktoivola          #+#    #+#             */
/*   Updated: 2024/04/23 15:56:36 by ktoivola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	check_length(long n)
{
	int	i;

	i = 0;
	if (!n)
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

char	*ft_itoa(int n)
{
	char	*ptr;
	long	num;
	int		count;

	num = n;
	count = check_length(num);
	ptr = malloc(sizeof(char) * count + 1);
	if (!ptr)
		return (0);
	if (!n)
		ptr[0] = '0';
	if (num < 0)
	{
		num = num * -1;
		ptr[0] = '-';
	}
	ptr[count] = 0;
	while (num)
	{
		ptr[--count] = '0' + (num % 10);
		num /= 10;
	}
	return (ptr);
}
