/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 17:01:30 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/01 16:06:22 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

int	ft_printf(const char *str, ...)
{
	va_list		args;
	int			i;

	i = 0;
	va_start(args, str);
	while (*str != '\0' )
	{
		if (*str == '%')
		{
			str++;
			if (*str == 's')
				ft_printf_str(&i, va_arg(args, char *));
			else if (*str == 'p' || *str == 'd' || *str == 'i' || *str == 'c')
				ft_printf_ptr((unsigned long)(va_arg(args, void *)), &i, *str);
			else if (*str == 'x' || *str == 'X' || *str == 'u')
				ft_print_hex(va_arg(args, unsigned int), *str, &i);
			else if (*str == '%')
				ft_printf_perc(&i);
		}
		else
			ft_printf_char(&i, *str);
		str++;
	}
	va_end(args);
	return (i);
}
