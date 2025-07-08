/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:47 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/08 16:14:24 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_handel(t_cmds *cmd)
{
	int	outfile;
	int infile;
	int	i;

	i = 0;
	infile = -1;
	outfile = -1;
	while (cmd && cmd->inoutfile && cmd->inoutfile[i] && cmd->inoutfile[i + 1])
	{
		if (ft_strcmp(cmd->inoutfile[i], ">") == 0)
		{
			if (outfile != -1)
				close(outfile);
			outfile = open (cmd->inoutfile[i + 1], O_CREAT | O_WRONLY | O_TRUNC , 0644);
			if (outfile == -1)
				return (perror(""), 0);
			printf("mamima: %d\n", outfile);
		}
		else if (ft_strcmp(cmd->inoutfile[i], ">>") == 0)
		{
			if (outfile != -1)
				close(outfile);
			outfile = open (cmd->inoutfile[i + 1], O_CREAT | O_WRONLY | O_APPEND , 0644);
			if (outfile == -1)
				return (perror(""), 0);
		}
		// cmd.herdoc 
		else if (ft_strcmp(cmd->inoutfile[i], "<<") == 0)
		{
			infile = cmd->heredoc_fd;
		}
		else if (ft_strcmp(cmd->inoutfile[i], "<") == 0)
		{
			if (infile != -1 && cmd->heredoc_fd == -1)
				close(infile);
			infile = open (cmd->inoutfile[i + 1], O_RDONLY);
			if (infile == -1)
				return (perror(""), 0);
		}
		i += 2;
	}

	if (infile > 0)
	{
		if(dup2(infile, 0) == -1)
			return (perror(""), 0);
		close(infile);
	}
	if (outfile > 0)
	{
		if(dup2(outfile, 1) == -1)
			return (perror(""), 0);
		close(outfile);
	}
	return (1);
}

void save_fd(int *in, int *out)
{
	*in = dup(0);  // 3
	*out = dup(1); // 4
}

void restore_fd(int *org_in, int *org_out)
{
	dup2(0, *org_in);
	dup2(1, *org_out);
}

void handle_single_command (t_cmds *cmd, t_env *env)
{
	char	**env_list;
	char	*cmd_path;
	pid_t		id;
	int		status = 0;
	int redirection_check = 0;
	int origin_stdin; // 3
	int origin_stdout;// 4
	
	if (!cmd->cmd[0])
		return ;
	save_fd(&origin_stdin, &origin_stdout);
	// saving int outfile
	id = fork();
	if (id == 0)
	{
		redirection_check =  redirection_handel(cmd);
		if (redirection_check == -1)
		{
			printf("Error redirection failed\n");
			exit(1);
		}
		env_list = env_to_array(env);
		cmd_path = check_command_is_exist(env, cmd->cmd[0]);
		printf("my final cmd is 2: %s\n", cmd_path);

		if (!cmd_path)
			return ;
		if (execve(cmd_path, cmd->cmd, env_list) < 0)
		{	
			if (errno == EACCES)
				return (printf("minishell 4: Permission denied\n"), exit(126));
			else if (errno == ENOENT)
				return (printf("minishell 5: NO such file or directory\n"), exit(127));
			else if (errno == ENOTDIR)
				return (printf("minishell 6: Not ad directory\n"), exit(126));
		}
	}
	else
	{
		waitpid(id, &status, 0);
		if(WIFEXITED(status))
			exit_status(WEXITSTATUS(status), 0);
	}
	restore_fd(&origin_stdin, &origin_stdout);
}
