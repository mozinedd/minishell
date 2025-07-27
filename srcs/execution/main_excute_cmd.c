/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_excute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/08 16:25:51 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/27 21:57:24 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cmdsize(t_cmds *cmd)
{
	t_cmds	*curr;
	int		counter;

	curr = cmd;
	counter = 0;
	if (!curr)
		return (0);
	while (curr)
	{
		counter++;
		curr = curr->next;
	}
	return (counter);
}

void	execute_command(t_glob *global)
{
	int	ft_cmd_size;
	int	fd[2];

	fd[0] = dup(0);
	fd[1] = dup(1);
	ft_cmd_size = ft_cmdsize(global->cmd);
	if (ft_cmd_size > 1)
		multiple_command(global, 1);
	else
		single_command(global, 0);
	while (wait(0) != -1)
		;
	dup2(fd[0], 0);
	dup2(fd[1], 1);
	close(fd[0]);
	close(fd[1]);
}
