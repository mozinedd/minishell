/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:55:57 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/21 20:08:02 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_command(t_cmds *cmd, t_glob *global, int *prev_fd)
{
	char **env_list;
	char *cmd_path;
	int fd[2];
	pid_t pid;
	int status = 0;
	int redirection_check = 0;

	if (cmd->next && pipe(fd) < 0)
	{
		perror("error in pipe");
		return (-1);
	}
	pid = fork();
	if (pid < 0)
	{
		perror("error in fork");
		close(fd[0]);
		close(fd[1]);
		return (-1);
	}
	if (pid == 0)
	{
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
		redirection_check =  redirection_handel(cmd->file);
		if (redirection_check == -1)
		{
			perror("Error redirection failed\n");
			exit(1);
		}
		if (check_is_builtin(cmd))
		{
			if (exec_is_builtin(&global->env, cmd) == 1)
				exit(1);
		}
		else
		{
			cmd_path = check_command_is_exist(global->env, cmd->cmd[0]);
			if (!cmd_path)
				exit(127);
			env_list = env_to_array(global->env);
			if (execve(cmd_path, cmd->cmd, env_list) < 0)
			{
				if (errno == EACCES)
					return (printf("minishell 4: Permission denied\n"), exit(126), 0);
				else if (errno == ENOENT)
					return (printf("minishell 5: NO such file or directory\n"), exit(127), 0);
				else if (errno == ENOTDIR)
					return (printf("minishell 6: Not ad directory\n"), exit(126), 0);
			}
		}
	}
	else if (pid > 0)
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		if (cmd->next)
		{
			close(fd[1]);
			*prev_fd = fd[0]; // Save read end for next command
		}
		else
			*prev_fd = -1;	
		if (!cmd->next)
		{
			waitpid(pid, &status, 0);
			exit_status(get_status_code(status), 0);
		} 
	}
	return (1);
}


void handle_multiple_command(t_glob *global)
{
	t_cmds	*cmd;
	int prev_fd = -1;

	cmd = global->cmd;
	while (cmd)
	{
		if (exec_command(cmd, global, &prev_fd) == -1)
			break ;
		cmd = cmd->next;
	}
	 if (prev_fd != -1)
		close(prev_fd);
	int status;
	while (wait(&status) > 0)
		 ;
}