/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbhatta <sbhatta@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 19:19:34 by sbhatta           #+#    #+#             */
/*   Updated: 2023/07/01 16:06:24 by sbhatta          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ft_printf.h"

void	ft_printf_str(int *i, char *str)
{
	if (str == NULL)
	{
		ft_putstr_fd("(null)", 2);
		*i += 6;
	}
	else
	{
		ft_putstr_fd(str, 2);
		*i += ft_strlen(str);
	}
}
