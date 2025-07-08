#include "minishell.h"

t_commands	*parsing(t_glob *global)
{
	char	*line;

	if (!global)
		return (NULL);
	line = read_command_line(global, global->exit_status);
	if (!line)
		return (NULL);
	global->token = lexer(line, global);
	if (!global->token)
		return (NULL);
	if (!check_redirections(global->token, global))
	{
		free_tokens(global->token);
		global->exit_status = 258;
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

	global = malloc(sizeof(t_glob));
	if (!global)
		return (NULL);
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
	if (!list_of_env(envp))
		return (perror("msh: environment failed"), 0);
	init_signals();
	while (1 && global)
	{
		global->cmd = parsing(global);
		if (open_heredoc(global))
		{
			close_heredoc(global);
			free_commands(global->cmd);
			continue ;
		}
		if (global->cmd)
		{
			// execution
			free_commands(global->cmd);
		}
		// execution_terminal
	}
	return (free(global), 1);
}
