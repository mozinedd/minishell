#include "minishell.h"

// int main (int argc, char ** argv , char **env)
// {
//     // t_environment *evnp;
//     // t_environment *current;
//     // (void)argv;
//     // (void)argc;
//     // (void)env;
//     // evnp = list_of_env(env);
//     // current = evnp;
//     // while (current)
//     // {
//     //     printf("%s=%s\n", current->key, current->value);
//     //     current = current->next;
//     // }

    void free_command_list(t_cmds *cmd) 
    {
        while (cmd) {
            t_cmds *next = cmd->next;
            if (cmd->cmd) {
                for (int i = 0; cmd->cmd[i]; i++)
                    free(cmd->cmd[i]);
                free(cmd->cmd);
            }
    
            if (cmd->inoutfile) {
                for (int i = 0; i < 3 && cmd->inoutfile[i]; i++)
                    free(cmd->inoutfile[i]);
                free(cmd->inoutfile);
            }
    
            free(cmd);
            cmd = next;
        }
    }

	int ft_cmdsize(t_cmds *cmd)
	{
		t_cmds *curr = cmd;
		int counter = 0;
		
		if (!curr)
			return 0;
		while(curr){
			counter++;
			curr = curr->next;
		}
		return counter;
	}
    
    void execute_command(t_cmds *cmd, t_env *env)
    {
        int ft_cmd_size = 0;
		(void)cmd;
		(void)env;

		// t_commands *current;
		// current = cmd;
		// while(current)
		// {
		// 	printf("the command 0 is : %s\n", current->cmd[0]);
		// 	printf("the command 1 is : %s\n", current->cmd[1]);
		// 	printf("the command 2 is : %s\n", current->cmd[2]);
		// 	printf("the inoutfile 0 is : %s\n", current->inoutfile[0]);
		// 	printf("the inoutfile 1 is : %s\n", current->inoutfile[1]);
		// 	current = current->next;
		// }

        // ft_cmd_size = ft_cmdsize(cmd);
		ft_cmd_size = 1;
        if (ft_cmd_size > 1)
        {
            printf("handle multiple command\n");
            // handle_multiple_command(cmd, env);
        }
        else
        {
			if (check_is_builtin(cmd))
				exec_is_builtin(&env, cmd);
			else
				handle_single_command(cmd, env);
        }
    }
    
    char *get_line(const char *prompt) {
        char *line = readline(prompt);
        if (!line) {
            printf("exit\n"); // Bash-like behavior on Ctrl+D
            return NULL;
        }
        if (*line)
            add_history(line);
        return line;
    }
    
    char **get_command_args() {
        char **args = malloc(sizeof(char *) * 100);
        int i = 0;
        char *input = get_line("Command (e.g. ls): ");
        if (!input) {
            free(args);
            return NULL;
        }
        args[i++] = input;
    
        while (1) {
            char prompt[64];
            sprintf(prompt, "Argument #%d (or just ENTER to skip): ", i);
            char *arg = get_line(prompt);
            if (!arg || strlen(arg) == 0) {
                free(arg);
                break;
            }
            args[i++] = arg;
        }
        args[i] = NULL;
        return args;
    }
    
    char **get_redirection() {
        char **redir = calloc(4, sizeof(char *));
        redir[0] = get_line("Redirection (<, >, >>, << or ENTER to skip): ");
        if (!redir[0]) {
            free(redir);
            return NULL;
        }
    
        if (strlen(redir[0]) > 0) {
            if (strcmp(redir[0], "<") == 0)
                redir[2] = strdup("in");
            else if (strcmp(redir[0], ">") == 0 || strcmp(redir[0], ">>") == 0)
                redir[2] = strdup("out");
            else if (strcmp(redir[0], "<<") == 0)
                redir[2] = strdup("heredoc");
            else {
                printf("Invalid redirection operator.\n");
                free(redir[0]);
                free(redir);
                return NULL;
            }
    
            redir[1] = get_line(strcmp(redir[2], "heredoc") == 0 ?
                                "Here-document delimiter: " : "Redirection file: ");
            if (!redir[1]) {
                free(redir[0]);
                free(redir[2]);
                free(redir);
                return NULL;
            }
        } else {
            free(redir[0]);
            redir[0] = NULL;
        }
    
        return redir;
    }
    
    t_cmds *create_command() {
        t_cmds *cmd = calloc(1, sizeof(t_cmds));
        cmd->cmd = get_command_args();
        if (!cmd->cmd) {
            free(cmd);
            return NULL;
        }
    
        cmd->inoutfile = get_redirection();
        return cmd;
    }
    
    t_cmds *build_command_list() {
        t_cmds *head = NULL;
        t_cmds *prev = NULL;
        int index = 1;
    
        while (1) {
            printf("\n--- Command #%d ---\n", index++);
            t_cmds *cmd = create_command();
            if (!cmd)
                break;
    
            if (!head)
                head = cmd;
            if (prev) {
                prev->next = cmd;
                cmd->prev = prev;
            }
            prev = cmd;
    
            char *more = get_line("Add a pipe to another command? (y/n): ");
            if (!more || strcmp(more, "y") != 0) {
                free(more);
                break;
            }
            free(more);
        }
        return head;
    }
    
  

    int main(int argc, char *argv[], char **env) {
        (void)argc;
        (void)argv;
        (void)env;

        t_env *env_struct =  list_of_env(env);

        // t_environment *current = env_struct;
        // while (current) {
        //     printf("Key : %s\n", current->key);
        //     printf("Value : %s\n", current->value);
        //     current = current->next;
        // }
        while (1) {
            t_cmds *cmd_list = build_command_list();
            if (!cmd_list)
                break;
    
            if (!cmd_list->cmd || !cmd_list->cmd[0]) {
                free_command_list(cmd_list);
                continue;
            }
    
            if (strcmp(cmd_list->cmd[0], "exit") == 0) {
                free_command_list(cmd_list);
                printf("Bye 👋\n");
                break;
            }
             
            execute_command(cmd_list, env_struct);
            free_command_list(cmd_list); 
        }
    
        return 0;
    }


	/// t_env *env_struct =  list_of_env(env);
	/// execute_command(cmd_list, env_struct);