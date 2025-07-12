/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_commands.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 16:55:57 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/12 16:06:05 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void exec_command(t_cmds *cmd, t_glob *global, int *prev_fd)
{
    char    **env_list;
    char    *cmd_path;
    int redirection_check = 0;
    int fd[2];
    pid_t pid;

    if (cmd->next && pipe(fd) < 0)
    {
        perror("error in pipe");
        return;
    }

    pid = fork();
    if (pid == 0)
    {
        // Child process
        if (cmd->next)
        {
            // Setup output pipe if there's a next command
            close(fd[0]);  // Close read end in child
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
        
        if (*prev_fd != -1)
        {
            // Setup input from previous pipe
            dup2(*prev_fd, STDIN_FILENO);
            close(*prev_fd);
        }

        // Handle redirections
        redirection_check = redirection_handel(global);
        if (redirection_check == -1)
        {
            perror("Error redirection failed\n");
            exit(1);
        }

        // Execute command
        env_list = env_to_array(global->env);
        cmd_path = check_command_is_exist(global->env, cmd->cmd[0]);
        if (!cmd_path)
            exit(127);
            
        if (execve(cmd_path, cmd->cmd, env_list) < 0)
        {
            if (errno == EACCES)
                exit(126);
            else if (errno == ENOENT)
                exit(127);
            else if (errno == ENOTDIR)
                exit(126);
            exit(1);
        }
    }
    else if (pid > 0)
    {
        // Parent process
        if (*prev_fd != -1)
            close(*prev_fd);  // Close previous pipe input
            
        if (cmd->next)
        {
            close(fd[1]);     // Close write end in parent
            *prev_fd = fd[0]; // Save read end for next command
        }
        else
            *prev_fd = -1;
            
        // If this is the last command, wait for it
        if (!cmd->next)
        {
            int status;
            waitpid(pid, &status, 0);
            exit_status(get_status_code(status), 0);
        }
    }
}

void handle_multiple_command(t_glob *global)
{
    int origin_stdin;
    int origin_stdout;
    int prev_fd = -1;
    t_cmds *cmd = global->cmd;

    save_fd(&origin_stdin, &origin_stdout);

    while (cmd)
    {
        exec_command(cmd, global, &prev_fd);
        cmd = cmd->next;
    }

    // Close any remaining pipe fd
    if (prev_fd != -1)
        close(prev_fd);

    restore_fd(&origin_stdin, &origin_stdout);

    // Wait for any remaining background processes
    int status;
    while (wait(&status) > 0)
        ; // Just wait for all children to finish
}


// void exec_command(t_cmds *cmd, t_glob *global, int *prev_fd)
// {
// 	char	**env_list;
// 	char	*cmd_path;
// 	int redirection_check = 0;
// 	// int status;
// 	int fd[2];


// 	if (cmd->next && pipe(fd) < 0)
// 	{
// 		perror("error in pipe");
// 		return ;
// 	}

// 	// printf("pipe[0]: %d, pipe[1]: %d\n\n",fd[0], fd[1]);

// 	pid_t id = fork();
// 	if (id == 0)
// 	{
// 		// ft_printf("am over her in child \n");
// 		if (cmd->next)
// 		{
// 			if (*prev_fd != -1)
// 			{
// 				dup2(*prev_fd, STDIN_FILENO);
// 				close(*prev_fd);
// 			}
// 			// close(fd[0]);
// 			close(fd[0]);
// 			dup2(fd[1], STDOUT_FILENO);
// 			close(fd[1]);  
// 			// close(fd[1]);
// 			// 	perror("dup2 in child failed: ");
// 			// close(fd[0]);
// 		}
// 		redirection_check =  redirection_handel(global);
// 		if (redirection_check == -1)
// 		{
// 			perror("Error redirection failed\n");
// 			exit(1);
// 		}
// 		env_list = env_to_array(global->env);
// 		cmd_path = check_command_is_exist(global->env, cmd->cmd[0]);
// 		printf("cmd Path: %s \n\n", cmd_path);
// 		if (!cmd_path)
// 			exit(0);
// 		if (execve(cmd_path, global->cmd->cmd, env_list) < 0)
// 		{	
// 			if (errno == EACCES)
// 				return (printf("minishell 4: Permission denied\n"), exit(126));
// 			else if (errno == ENOENT)
// 				return (printf("minishell 5: NO such file or directory\n"), exit(127));
// 			else if (errno == ENOTDIR)
// 				return (printf("minishell 6: Not ad directory\n"), exit(126));
// 		}
// 	}
// 	else
// 	{
// 		if (*prev_fd != -1)
//     		close(*prev_fd);
// 		if (cmd->next)
//     		close(fd[1]);
// 		// ft_printf("am over her in parent\n");
// 		*prev_fd = (cmd->next) ? fd[0] : -1;
// 		// close(fd[1]);
// 		// dup2(fd[0], 0);
// 		// close(fd[0]);
// 		// waitpid(id, &status, 0);
// 		// exit_status(get_status_code(status), 0);
// 	}
// }


// void handle_multiple_command(t_glob *global)
// {
// 	int origin_stdin;
// 	int origin_stdout;
// 	int status;
// 	int prev_fd;
// 	t_cmds *cmd;

// 	save_fd(&origin_stdin, &origin_stdout);
// 	// execution
// 	cmd = global->cmd;
// 	// int i = 0;
// 	// while(cmd)
// 	// {
// 	// 	i++;
// 	// 	if(cmd->cmd[i] == NULL)
// 	// 	{
// 	// 		i = 0;
// 	// 		cmd = cmd->next;
// 	// 	}
// 	// }
// 	prev_fd = -1;
// 	while (cmd)
// 	{
// 		exec_command(cmd, global, &prev_fd);
// 		// printf("-==============> cmd: %s\n", cmd->cmd[0]);
// 		cmd = cmd->next;
// 	}

//     if (prev_fd != -1)
// 		close(prev_fd);

// 	restore_fd(&origin_stdin, &origin_stdout);
// 	// waiting over her
// 	while (wait(&status) != -1){
// 		exit_status(get_status_code(status), 0);
// 	}
// }




// #include <stdio.h>
// #include <unistd.h>
// #include <sys/wait.h>


// int exec_cmd(char *path, char **args, char **envp, int is_not_last)
// {
// 	int fd[2];

// 	if (is_not_last)
// 	{
// 		int fail = pipe(fd);
// 		if (fail < 0)
// 			printf("error in pipe\n");
// 	}
// 	int pid = fork();
// 	if (pid == 0)
// 	{
// 		if (is_not_last)
// 		{
// 			if (dup2(fd[1], 1) < 0)
// 				perror("dup2 in child failed: ");
// 			close(fd[0]);
// 			close(fd[1]);
// 		}
// 		execve(path, args, envp);
// 	}
// 	else     
// 	{
// 		dup2(fd[0], 0);
// 		close(fd[1]);
// 		close(fd[0]);
// 		int status;
// 		waitpid(pid, &status, 0);
// 		if (WIFEXITED(status))
// 			return (WEXITSTATUS(status));
// 	}
// 	return (0);
// }

// int main(int ac, char **av, char **envp)
// {
// 	// char *cmd_one[] = {"ls", "-la", NULL};
// 	char *cmd_one[] = {"ls", "-la", NULL};
// 	char *cmd_two[] = {"grep", "mini", NULL};
// 	char *cmd_tree[] = {"rev", NULL};
// 	int status = 0;

// 	int stdincopy = dup(0);
// 	status = exec_cmd("/bin/ls", cmd_one, envp, 1);
// 	status = exec_cmd("/bin/grep", cmd_two, envp, 1); 
// 	status = exec_cmd("/bin/rev", cmd_tree, envp, 0); 
// 	dup2(stdincopy, 0);
// 	close(stdincopy);
// 	printf("=====> Status is: %d\n", status);
// }