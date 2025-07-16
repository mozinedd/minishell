#include "minishell.h"

t_cmds	*parsing(t_glob *global)
{
	char	*line;

	if (!global)
		return (NULL);
	line = read_command_line();
	if (!line)
		return (NULL);
	global->token = lexer(line, global);
	if (!global->token)
		return (NULL);
	if (!check_redirections(global->token))
	{
		// free_tokens(global->token);
		exit_status(258, 0);
		return (NULL);
	}
	global->cmd = create_commands(global);
	global->cmd = final_commandes(&global->cmd);
	if (!global->cmd)
		return (NULL);
	return (global->cmd);
}

t_glob	*init_global_struct(void)
{
	t_glob	*global;

	global = gc_malloc(sizeof(t_glob));
	global->cmd = NULL;
	global->token = NULL;
	global->env = NULL;
	global->in_double_quotes = 0;
	global->exit_status = 0;
	return (global);
}

int	mshll_loop(char **envp)
{
	t_glob	*global;
	char	**cmd;

	global = init_global_struct();
	cmd = gc_malloc(sizeof(char*) * 5);
	if (!cmd)
		return (perror("msh: malloc failed"), 0);
	if (!global)
		return (perror("msh: error allocating memory"), 0);
	t_env* env = list_of_env(envp);
	if (!env)
	{
		cmd[0] = ft_strdup("export");
		cmd[1] = ft_strdup("PWD=/mnt/homes/mozinedd/Desktop/linux-verion-mini");
		cmd[2] = ft_strdup("SHLVL=1");
		cmd[3] = ft_strdup("_=/usr/bin/env");
		cmd[4] = NULL;
		ft_export(&env, cmd);
	}
	global->env = env;
	init_signals();
	while (1 && global)
	{
		dup2(2, 0);
		dup2(2, 1);
		global->cmd = parsing(global);
		if (open_heredoc(global))
		{
			close_heredoc(global);
			continue ;
		}
		if (global->cmd)
		{
			execute_command(global);
			close_heredoc(global);
		}
	}
	gc_free();
	return (/*free(global), */1);
}

// void f(void) { system("leaks minishell"); }
int main (int args, char **argv, char **env)
{
	// atexit(f);
	(void)args;
	(void)argv;
	
	// t_cmds *cmd = gc_malloc(sizeof(t_cmds));
	// gc_free();
	// (void)cmd;
	// return 0;

	mshll_loop(env);
	
	return 1;
}
