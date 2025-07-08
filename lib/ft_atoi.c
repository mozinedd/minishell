/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 11:46:13 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/03 22:04:32 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	detect_overflow(int is_set, int my_status)
{
	static int	status;
	if (is_set == 1)
		status = my_status;
	return status;
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	long	r;
	long	holder;

	i = 0;
	s = 1;
	r = 0;
	holder = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s *= -1;
		i++;
	}
	while (str[i] != '\0' && str[i] >= '0' && str[i] <= '9')
	{
		r = r * 10 + (str[i] - '0');
		if (r < holder)
			return (detect_overflow(1, 13));
		holder = r;
		i++;
	}
	return (s * r);
}

//1234
// 1235
// 123  holder = 123 : r = -1233
//
//
//

