/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <davguerr@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 00:15:48 by david             #+#    #+#             */
/*   Updated: 2026/10/09 01:18:59 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_int(int n)
{
	char	c;
	int		count;
	long	num;

	count = 0;
	num = n;
	if (num < 0)
	{
		count += write(1, "-", 1);
		num = num * -1;
	}
	if (num >= 10)
		count += print_int(num / 10);
	c = num % 10 + '0';
	count += write(1, &c, 1);
	return (count);
}

int	print_uns(unsigned int n)
{
	char	c;
	int		count;
	long	num;

	num = n;
	count = 0;
	if (num >= 10)
		count += print_uns(num / 10);
	c = num % 10 + '0';
	count += write(1, &c, 1);
	return (count);
}
