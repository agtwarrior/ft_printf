/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <davguerr@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/05 19:12:07 by david             #+#    #+#             */
/*   Updated: 2026/10/09 01:15:29 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	manage_print(char type, va_list *args)
{
	if (type == 'c')
		return (print_char(va_arg(*args, int)));
	if (type == 's')
		return (print_str(va_arg(*args, char *)));
	if (type == 'd' || type == 'i')
		return (print_int(va_arg(*args, int)));
	if (type == 'u')
		return (print_uns(va_arg(*args, unsigned int)));
	if (type == 'x')
		return (print_lhexa(va_arg(*args, unsigned int)));
	if (type == 'X')
		return (print_uhexa(va_arg(*args, unsigned int)));
	if (type == 'p')
		return (print_ptr(va_arg(*args, void *)));
	if (type == '%')
		return (write (1, "%", 1));
	write (1, "%", 1);
	write (1, &type, 1);
	return (2);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	size_t	i;
	int		count;

	if (!str)
		return (0);
	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			count += manage_print(str[++i], &args);
		}
		else
			count += write (1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
