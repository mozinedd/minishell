/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:15:25 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 21:15:26 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_digit(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		count;
	char	*pnt;
	long	num;
	int		i;

	num = n;
	count = count_digit(n);
	pnt = gc_malloc(sizeof(char) * (count + 1));
	pnt[count] = '\0';
	if (num < 0)
	{
		pnt[0] = '-';
		num = -num;
	}
	i = count - 1;
	while (num > 0)
	{
		pnt[i--] = (num % 10) + '0';
		num /= 10;
	}
	if (n == 0)
		pnt[0] = '0';
	return (pnt);
}
