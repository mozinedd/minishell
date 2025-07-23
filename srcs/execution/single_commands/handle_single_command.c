/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:47 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 19:50:32 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_append(int *outfile, t_file *tmp, int i)
{
	if (tmp[i].value == NULL || size_cmd(tmp[i].value) != 1)
		return (ft_printf("msh : ambiguous redirect\n"), -1);
	if (*outfile != -1)
		close(*outfile);
	*outfile = open (tmp[i].value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*outfile == -1)
		return (perror("Error redirection failed"), -1);
	return (1);
}

int	redirection_redir_out(int *outfile, t_file *tmp, int i)
{
	if (!tmp[i].value || size_cmd(tmp[i].value) != 1)
		return (ft_printf("msh : ambiguous redirect\n"), -1);
	if (*outfile != -1)
		close(*outfile);
	*outfile = open (tmp[i].value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile == -1)
		return (perror("Error redirection failed\n"), -1);
	return (1);
}

int	redirection_redir_in(int *infile, t_file *tmp, int i)
{
	if (tmp[i].value == NULL || size_cmd(tmp[i].value) != 1)
		return (ft_printf("msh : ambiguous redirect\n"), -1);
	if (*infile != -1 && tmp[i].fd == -1)
		close(*infile);
	*infile = open (tmp[i].value, O_RDONLY);
	if (*infile == -1)
		return (perror("Error redirection failed\n"), -1);
	return (1);
}

int	all_redirection_checker(int i, int *outfile, int *infile, t_file *tmp)
{
	if (tmp[i].type == REDIR_OUT)
	{
		if (redirection_redir_out(outfile, tmp, i) == -1)
			return (-1);
	}
	else if (tmp[i].type == APPEND)
	{
		if (redirection_append(outfile, tmp, i) == -1)
			return (-1);
	}
	else if (tmp[i].type == HERDOC)
		*infile = tmp[i].fd;
	else if (tmp[i].type == REDIR_IN)
	{
		if (redirection_redir_in(infile, tmp, i) == -1)
			return (-1);
	}
	return (1);
}

int	redirection_handel(t_file *tmp)
{
	int	outfile;
	int	infile;
	int	i;

	infile = -2;
	outfile = -2;
	i = -1;
	while (tmp && tmp[++i].type)
	{
		if (all_redirection_checker(i, &outfile, &infile, tmp) == -1)
			return (-1);
	}
	if (infile > 0)
	{
		if (dup2(infile, 0) == -1)
			return (perror(""), -1);
		close(infile);
	}
	if (outfile > 0)
	{
		if (dup2(outfile, 1) == -1)
			return (perror(""), -1);
		close(outfile);
	}
	return (1);
}

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

	redirection_check = 0;
	signal(SIGQUIT, SIG_DFL);
	signal(SIGINT, SIG_DFL);
	redirection_check = redirection_handel(global->cmd->file);
	if (redirection_check == -1 || !global->cmd->cmd[0])
		exit(1);
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

void	handle_single_command(t_glob *global)
{
	pid_t	id;
	int		status;

	status = 0;
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
