/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:17 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/03 16:23:18 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_hander;

char	*read_command_line(t_glob *global, int exit_stat)
{
	char	*line;

	line = NULL;
	line = readline("minishell$ ");
	if (g_sig_hander == CTRL_C)
	{
		global->exit_status = 1;
		g_sig_hander = 0;
	}
	if (!line)
	{
		rl_clear_history();
		/* free_env(global->env); */
		free(global);
		write(2, "exit\n", 5);
		exit(exit_stat);
	}
	else if (*line)
		add_history(line);
	else
		return (free(line), NULL);
	return (line);
}

void	skip_to_next(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if (str[*i])
		(*i)++;
}
