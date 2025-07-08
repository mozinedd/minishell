#include "minishell.h"

void print_commands(t_commands *commands)
{
    t_commands *cmd = commands;
    while (cmd)
    {
        printf("Command:\n");
        if (cmd->cmd)
        {
            char **cmd_args = cmd->cmd;
            while (*cmd_args)
            {
                printf("  Argument: %s\n", *cmd_args);
                cmd_args++;
            }
        }
        printf("Files:\n");
        t_file *file = cmd->file;
        while (file && file->type != 0)
        {
            printf("  file ==> word : %s ", file->value);
            if (file->type == HERDOC)
                printf("---- type : HERDOC\n");
            if (file->type == REDIR_IN)
                printf(" ----- type  : REDIR_IN\n");
            if (file->type == APPEND)
                printf(" ----- type : APPEND\n");
            if (file->type == REDIR_OUT)
                printf(" ---- type : REDIR_OUT\n");
            file++;
        }
        cmd = cmd->next;
    }
}

int main()
{
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
        t_commands *commands = create_commands(token);
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