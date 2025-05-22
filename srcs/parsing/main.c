#include "minishell.h"

void print_commands(t_commands *commands)
{
    t_commands *cmds = commands;
    while (cmds)
    {
        // Affichage des arguments de la commande
        printf("Command:\n");
        if (cmds->cmd)
        {
            char **cmd_args = cmds->cmd;
            while (*cmd_args)
            {
                printf("  Argument: %s\n", *cmd_args);
                cmd_args++;
            }
        }

        // Affichage des fichiers associés à la commande
        printf("Files:\n");
        t_file *file = cmds->file;
        while (file && file->type != 0) // Vérifie que le fichier existe et a un type valide
        {
            printf("  File ==> word: %s ", file->value);
            switch (file->type)
            {
                case HERDOC:
                    printf("---- type: HERDOC\n");
                    break;
                case REDIR_IN:
                    printf("----- type: REDIR_IN\n");
                    break;
                case APPEND:
                    printf("----- type: APPEND\n");
                    break;
                case REDIR_OUT:
                    printf("---- type: REDIR_OUT\n");
                    break;
                default:
                    printf("---- type: UNKNOWN\n");
                    break;
            }
            file++;
        }

        // Passer à la commande suivante
        cmds = cmds->next;
    }
}

int main (int argc, char ** argv , char **env)
{
    t_environment *evnp;
    // t_environment *current;
    (void)argv;
    (void)argc;

    evnp = list_of_env(env);
    // current = evnp;
    // while (current)
    // {
    //     printf("%s=%s\n", current->key, current->value);
    //     current = current->next;
    // }
    char *str;
    t_tokens *token;

    while (1)
    {
        str = read_command_line(); 
        if (!str)
        {
            printf("exit\n");
            break;
        }
        token = tokenize_cmd(str); 
        if (!token)
        {
            free(str);
            continue;
        }
        if (!syntax_error(&token))
        {
            free_token(token);
            free(str);
            continue;
        }
        t_tokens *tmp = token;
        while (tmp)
        {
            printf("Token: %s     ==== ", tmp->str);
            if (tmp->type == WORD)
                printf("type WORD\n");
            if (tmp->type == PIPE)
                printf("type PIPE\n");
            if (tmp->type == HERDOC)
                printf("type HERDOC\n");
            if (tmp->type == REDIR_IN)
                printf("type REDIR_IN\n");
            if (tmp->type == APPEND)
                printf("type APPEND\n");
            if (tmp->type == REDIR_OUT)
                printf("type REDIR_OUT\n");
            tmp = tmp->next;
        }
        t_commands *commands = create_commands(token, evnp);
        commands = final_commandes(&commands);
        if (commands)
        {
            printf("\n\n=== Command Test ===\n");
            print_commands(commands);
        }
        free_commands(commands);
        free_token(token);
        free(str);
    }

    return 0;
}