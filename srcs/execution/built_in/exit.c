/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:07 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/05 15:29:08 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_numeric(char *str)
{
	int i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int ft_exit(char **args)
{
	int number;
	printf("exit\n");
	if (!args[1])
		exit(exit_status(0, 1));
	if (!is_numeric(args[1]))
	{
		fprintf(stderr, "exit: %s : numeric argument required\n", args[1]);
		exit (2);
	}
	if (args[2])
	{
		fprintf(stderr, "exit: too many argument\n");
		exit_status(1, 0);
		printf("exit status : %d\n", exit_status(1, 1));
		return (1);
	}
	number = ft_atoi(args[1]);
	if (detect_overflow(0, 1) == 13)
	{
		fprintf(stderr, "exit: %s : numeric argument required\n", args[1]);
		exit (2);
	}
	exit(number);
	return (0);
}
