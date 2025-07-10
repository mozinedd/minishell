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

	global = init_global_struct();
	if (!global)
		return (perror("msh: error allocating memory"), 0);
	t_env* env = list_of_env(envp);
	global->env = env;
	init_signals();
	while (1 && global)
	{
		global->cmd = parsing(global);
		if (open_heredoc(global))
		{
			close_heredoc(global);
			// free_commands(global->cmd);
			continue ;
		}
		if (global->cmd)
		{
			execute_command(global);
			// free_commands(global->cmd);
		}
	}
	gc_free();
	return (/*free(global), */1);
}
int main (int args, char **argv, char **env)
{
	(void)args;
	(void)argv;
	mshll_loop(env);
	return 1;
}
