/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hexa.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <davguerr@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/09 00:44:17 by david             #+#    #+#             */
/*   Updated: 2026/10/09 01:12:41 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_lhexa(unsigned int n)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += print_lhexa(n / 16);
	count += write(1, &base[n % 16], 1);
	return (count);
}

int	print_uhexa(unsigned int n)
{
	char	*base;
	int		count;

	base = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
		count += print_uhexa(n / 16);
	count += write(1, &base[n % 16], 1);
	return (count);
}

static int	print_addr(unsigned long n)
{
	char	*base;
	int		count;

	base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += print_addr(n / 16);
	count += write(1, &base[n % 16], 1);
	return (count);
}

int	print_ptr(void *ptr)
{
	int	count;

	if (!ptr)
		return (write(1, "(nil)", 5));
	count = write(1, "0x", 2);
	count += print_addr((unsigned long)ptr);
	return (count);
}
