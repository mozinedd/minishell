/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:55:57 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/28 17:42:26 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_fd(t_cmds *cmd, int *fd, int *prev_fd)
{
	int	redirection_check;

	redirection_check = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	if (cmd->next != NULL)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (*prev_fd != -1)
	{
		dup2(*prev_fd, STDIN_FILENO);
		close(*prev_fd);
	}
	redirection_check = redirection_handel(cmd->file);
	if (redirection_check == -1)
	{
		perror("redirection faield\n");
		exit(1);
	}
}

void	handle_normal_command(t_glob *global, t_cmds *cmd)
{
	char	*cmd_path;
	char	**env_list;

	cmd_path = check_command_is_exist(global->env, cmd->cmd[0]);
	if (!cmd_path)
		exit(127);
	env_list = env_to_array(global->env);
	if (execve(cmd_path, cmd->cmd, env_list) < 0)
	{
		if (errno == EACCES)
			return (printf("mini: Permission denied\n"), exit(126));
		else if (errno == ENOENT)
			return (printf("mini: NO such file or directory\n"), exit(127));
		else if (errno == ENOTDIR)
			return (printf("mini: Not ad directory\n"), exit(126));
	}
}

void	parent_process(int *prev_fd, t_cmds *cmd, int *fd, pid_t pid)
{
	int	status;

	status = 0;
	if (*prev_fd != -1)
		close(*prev_fd);
	if (cmd->next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	else
		*prev_fd = -1;
	if (!cmd->next)
	{
		waitpid(pid, &status, 0);
		exit_status(get_status_code(status), 0);
	}
}

int	exec_command(t_cmds *cmd, t_glob *global, int *prev_fd, int is_multi)
{
	int		fd[2];
	pid_t	pid;

	if (cmd->next && pipe(fd) < 0)
		return (perror("error in pipe"), -1);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), close(fd[0]), close(fd[1]), -2);
	if (pid == 0)
	{
		handle_fd(cmd, fd, prev_fd);
		if (check_is_builtin(cmd))
		{
			if (exec_is_builtin(&global->env, cmd, is_multi) == 1)
				exit(0);
		}
		else
			handle_normal_command(global, cmd);
	}
	else if (pid > 0)
		return (add_pid(&global->pids, pid),
			parent_process(prev_fd, cmd, fd, pid), 1);
	return (1);
}

void	multiple_command(t_glob *global, int is_multi)
{
	t_cmds	*cmd;
	int		prev_fd;
	int		status;
	int		fail;

	prev_fd = -1;
	cmd = global->cmd;
	while (cmd)
	{
		fail = exec_command(cmd, global, &prev_fd, is_multi);
		if (fail < 0)
			break ;
		cmd = cmd->next;
	}
	if (fail == -2)
		kill_pids(global->pids);
	global->pids = NULL;
	if (prev_fd != -1)
		close(prev_fd);
	while (wait(&status) > 0)
		;
}
