/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 20:23:07 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/11 22:11:54 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check(va_list args, char c)
{
	int	result;

	result = 0;
	if (c == 's')
		result += ft_print_str(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		result += ft_putnbr(va_arg(args, int));
	else
		result += ft_putchar_exec(c);
	return (result);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		result;
	va_list	args;

	i = 0;
	result = 0;
	va_start(args, format);
	if (write(1, "", 0) == -1)
		return (-1);
	while (format[i])
	{
		if (format[i] == '%' )
		{
			i++;
			if (format[i] == '\0')
				break ;
			result += ft_check(args, format[i]);
		}
		else
			result += ft_putchar_exec(format[i]);
		i++;
	}
	va_end(args);
	return (result);
}
