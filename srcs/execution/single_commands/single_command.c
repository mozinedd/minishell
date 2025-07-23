/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 18:58:42 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 22:26:10 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_status_code(int status)
{
	int	sig;
	int	last_status;

	sig = 0;
	last_status = 0;
	if (WIFEXITED(status))
		last_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		if (sig == SIGINT)
			last_status = SIGINT + 128;
		else if (sig == SIGQUIT)
		{
			dup2(2, 1);
			printf("Quit: %d\n", SIGQUIT);
			dup2(1, 2);
			last_status = SIGQUIT + 128;
		}
	}
	return (last_status);
}

int	handle_single_in_child(t_glob *global)
{
	char	**env_list;
	char	*cmd_path;
	int		redirection_check;

	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	redirection_check = redirection_handel(global->cmd->file);
	if (redirection_check == -1 || !global->cmd->cmd[0])
		exit(1);
	if (run_it_in_child(&global->env, global->cmd) == 1)
		return (exit_status(1, 0), exit(0), -1);
	env_list = env_to_array(global->env);
	cmd_path = check_command_is_exist(global->env, global->cmd->cmd[0]);
	if (!cmd_path)
		return (-1);
	if (execve(cmd_path, global->cmd->cmd, env_list) < 0)
	{
		if (errno == EACCES)
			return (ft_printf("mini: Permission denied\n"), exit(126), -1);
		else if (errno == ENOENT)
			return (ft_printf("mini: NO such file or dire\n"), exit(127), -1);
		else if (errno == ENOTDIR)
			return (ft_printf("mini: Not ad directory\n"), exit(126), -1);
	}
	return (1);
}

void	single_command(t_glob *global, int is_multi)
{
	pid_t	id;
	int		status;

	status = 0;
	if (run_it_in_parent(&global->env, global->cmd, is_multi) == 0)
	{
		id = fork();
		if (id == 0)
		{
			if (handle_single_in_child(global) == -1)
				return ;
		}
		else
		{
			waitpid(id, &status, 0);
			exit_status(get_status_code(status), 0);
		}
	}
}
