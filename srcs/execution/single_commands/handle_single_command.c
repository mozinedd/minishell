/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_single_command.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:47 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/19 20:19:55 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_handel(t_file *tmp)
{
	int	outfile;
	int infile;
	int	i;

	i = 0;
	infile = -2;
	outfile = -2;
	while (tmp && tmp[i].type)
	{
		// fprintf(stderr,"%s\n", tmp[i].value );
		// problem here when we have > $a normaly it is an error but in our program doesn't return error it is working
		if (tmp[i].type == REDIR_OUT)
		{
			if (!tmp[i].value || size_cmd(tmp[i].value) != 1)
				return (perror("msh : ambiguous redirect"), -1);
			if (outfile != -1)
				close(outfile);
			outfile = open (tmp[i].value, O_CREAT | O_WRONLY | O_TRUNC , 0644);
			if (outfile == -1)
				return (perror("Error redirection failed"), -1);
			printf("mamima: %d\n", outfile);
		}
		else if (tmp[i].type == APPEND)
		{
			if(tmp[i].value == NULL || size_cmd(tmp[i].value) != 1)
				return (printf("msh : ambiguous redirect"), -1);
			if (outfile != -1)
				close(outfile);
			outfile = open (tmp[i].value, O_CREAT | O_WRONLY | O_APPEND , 0644);
			if (outfile == -1)
				return (perror("Error redirection failed"), -1);
		}
		else if (tmp[i].type == HERDOC)
		{
			infile = tmp[i].fd;
		}
		else if (tmp[i].type == REDIR_IN)
		{
			if(tmp[i].value == NULL || size_cmd(tmp[i].value) != 1)
				return (printf("msh : ambiguous redirect"), -1);
			if (infile != -1 && tmp[i].fd == -1)
				close(infile);
			infile = open (tmp[i].value, O_RDONLY);
			if (infile == -1)
				return (perror("Error redirection failed"), -1);
		}
		i += 1;
	}
	if (infile > 0)
	{
		if(dup2(infile, 0) == -1)
			return (perror(""), -1);
		close(infile);
	}
	if (outfile > 0)
	{
		if(dup2(outfile, 1) == -1)
			return (perror(""), -1);
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
	dup2(*org_in, 0);
	close(*org_in);
	dup2( *org_out, 1);
	close(*org_out);
}

int get_status_code(int status)
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

void handle_single_command (t_glob *global)
{
	char	**env_list;
	char	*cmd_path;
	pid_t		id;
	int		status = 0;
	int redirection_check = 0;
	// int origin_stdin; // 3
	// int origin_stdout;// 4
	
	if (!global->cmd->cmd[0])
		return ;
	// save_fd(&origin_stdin, &origin_stdout);
	id = fork();
	if (id == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		signal(SIGINT, SIG_DFL); // katrod signal l difault dyalha;
		redirection_check =  redirection_handel(global->cmd->file);
		if (redirection_check == -1)
		{
			// perror("Error redirection failed\n");
			exit(1);
		}
		env_list = env_to_array(global->env);
		cmd_path = check_command_is_exist(global->env, global->cmd->cmd[0]);
		if (!cmd_path)
			return ;
		if (execve(cmd_path, global->cmd->cmd, env_list) < 0)
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
		exit_status(get_status_code(status), 0);
	}
	// restore_fd(&origin_stdin, &origin_stdout);
}
