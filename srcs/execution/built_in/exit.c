/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:07 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/20 21:44:13 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_numeric(char *str)
{
	int	i;

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

char	*skip_space(char *str)
{
	int	i;
	int	j;
	
	i = 0;
	j = ft_strlen(str) - 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	while (str[j] == ' ' || (str[j] >= 9 && str[j] <= 13))
		j--;
	return (ft_substr(str, i, (j + 1) - i));
}

int	ft_exit(char **args)
{
	int	number;
	char *skip;
	
	printf("exit \n");
	if (!args[1])
		exit(exit_status(0, 1));
	skip = skip_space(args[1]);
	if (!is_numeric(skip))
	{
		fprintf(stderr, "exit: %s : numeric argument required\n", args[1]);
		exit (255);
	}
	if (args[2])
	{
		fprintf(stderr, "exit: too many argument\n");
		exit_status(1, 0);
		return (1);
	}
	number = ft_atoi(skip);
	if (detect_overflow(0, 1) == 13)
	{
		fprintf(stderr, "exit: %s : numeric argument required\n", args[1]);
		exit (2);
	}
	return (exit(number), 0);
}
