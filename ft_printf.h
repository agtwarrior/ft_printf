/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: david <davguerr@student.42madrid.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/08 18:50:53 by david             #+#    #+#             */
/*   Updated: 2026/10/09 10:43:01 by david            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H

# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>
# include <stdlib.h>

int	print_char(char c);
int	print_str(char *str);
int	print_int(int n);
int	print_uns(unsigned int n);
int	print_lhexa(unsigned int n);
int	print_uhexa(unsigned int n);
int	ft_printf(char const *str, ...);
int	print_ptr(void *ptr);

#endif
