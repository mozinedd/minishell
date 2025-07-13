#include "minishell.h"

void exec_command(t_cmds *cmd, t_glob *global, int *prev_fd)
{
	char	**env_list;
	char	*cmd_path;
	int redirection_check = 0;
	// int status;
	int fd[2];


	if (cmd->next && pipe(fd) < 0)
	{
		perror("error in pipe");
		return ;
	}

	// printf("pipe[0]: %d, pipe[1]: %d\n\n",fd[0], fd[1]);

	pid_t id = fork();
	if (id == 0)
	{
		// ft_printf("am over her in child \n");
		if (cmd->next)
		{
			if (*prev_fd != -1)
			{
				dup2(*prev_fd, STDIN_FILENO);
				close(*prev_fd);
			}
			// close(fd[0]);
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);  
			// close(fd[1]);
			// 	perror("dup2 in child failed: ");
			// close(fd[0]);
		}
		redirection_check =  redirection_handel(global);
		if (redirection_check == -1)
		{
			perror("Error redirection failed\n");
			exit(1);
		}
		env_list = env_to_array(global->env);
		cmd_path = check_command_is_exist(global->env, cmd->cmd[0]);
		printf("cmd Path: %s \n\n", cmd_path);
		if (!cmd_path)
			exit(0);
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
		if (*prev_fd != -1)
    		close(*prev_fd);
		if (cmd->next)
    		close(fd[1]);
		// ft_printf("am over her in parent\n");
		*prev_fd = (cmd->next) ? fd[0] : -1;
		// close(fd[1]);
		// dup2(fd[0], 0);
		// close(fd[0]);
		// waitpid(id, &status, 0);
		// exit_status(get_status_code(status), 0);
	}
}


void handle_multiple_command(t_glob *global)
{
	int origin_stdin;
	int origin_stdout;
	int status;
	int prev_fd;
	t_cmds *cmd;

	save_fd(&origin_stdin, &origin_stdout);
	// execution
	cmd = global->cmd;
	// int i = 0;
	// while(cmd)
	// {
	// 	i++;
	// 	if(cmd->cmd[i] == NULL)
	// 	{
	// 		i = 0;
	// 		cmd = cmd->next;
	// 	}
	// }
	prev_fd = -1;
	while (cmd)
	{
		exec_command(cmd, global, &prev_fd);
		// printf("-==============> cmd: %s\n", cmd->cmd[0]);
		cmd = cmd->next;
	}

    if (prev_fd != -1)
		close(prev_fd);

	restore_fd(&origin_stdin, &origin_stdout);
	// waiting over her
	while (wait(&status) != -1){
		exit_status(get_status_code(status), 0);
	}
}
