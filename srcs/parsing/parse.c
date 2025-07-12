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



void print_cmds(t_glob *global) {
    t_cmds *cmd = global->cmd;
    int cmd_num = 1;

    // Colors
    const char *color_header = "\033[1;34m";    // Bright Blue
    const char *color_cmd_num = "\033[1;32m";   // Bright Green
    const char *color_arg_index = "\033[1;33m"; // Bright Yellow
    const char *color_arg_val = "\033[0;37m";   // Light Gray (normal)
    const char *color_reset = "\033[0m";        // Reset

    printf("%s=======================> Commands:%s\n", color_header, color_reset);
    while (cmd) {
        printf("%sCommand #%d:%s\n", color_cmd_num, cmd_num++, color_reset);

        if (cmd->cmd) {
            for (int i = 0; cmd->cmd[i]; i++) {
                printf("  %sargv[%d]: %s%s\n", color_arg_index, i, color_arg_val, cmd->cmd[i]);
            }
        } else {
            printf("  %s(no arguments)%s\n", color_arg_val, color_reset);
        }
        cmd = cmd->next;
    }
    printf("%s=======================< Commands:%s\n", color_header, color_reset);
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
			// print_cmds(global);
			execute_command(global);
			// free_commands(global->cmd);
		}
	}
	gc_free();
	return (/*free(global), */1);
}

void f(void) { system("lsof -c minishell"); }
int main (int args, char **argv, char **env)
{
	atexit(f);
	(void)args;
	(void)argv;
	mshll_loop(env);
	return 1;
}
