/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:28:36 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/01 16:06:27 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	ft_printf_ptr(unsigned long p, int *i, char ch)
{
	if (ch == 'c')
	{
		ft_putchar_fd(p, 2);
		(*i)++;
	}
	else if (ch == 'i' || ch == 'd')
	{
		ft_putnbr_fd((int)p, 2);
		*i += ft_printf_count((int)p);
	}
	else
	{
		ft_putstr_fd("0x", 2);
		ft_print_hex(p, 'x', i);
		*i += 2;
	}
}
