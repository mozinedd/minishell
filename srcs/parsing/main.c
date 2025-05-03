#include "minishell.h"

void f()
{
    char cmd[50];
    sprintf(cmd, "leaks %d", getpid());
    system(cmd);
}


int main()
{
    char *str ;
        t_tokens *token;
    atexit(f);
    while(1)
    {
        str = read_command_line();
        if(!str)
        {
            printf("exit\n");
            break;
        }
        token = tokenize_cmd(str);
        if(!token)
        {
            free(str);
            continue;
        }
        if (!syntax_error(&token))
        {
            free_token(token);
            continue;
        }
        t_tokens *tmp  = token;

        while(tmp)
        {
                printf("Token: %s     ==== ", tmp->str);
                if(tmp->type == WORD)
                    printf("type word\n");
                if(tmp->type == PIPE)
                    printf("type Pipe\n");
                if(tmp->type == HERDOC)
                    printf("type herdoc\n");
                if(tmp->type == REDIR_IN)
                    printf("type REDIR_IN\n");
                if(tmp->type ==APPEND)
                    printf("type APPEND\n");
                if(tmp->type ==REDIR_OUT)
                    printf("type REDIR_OUT\n");
                tmp = tmp->next;
        }
        free_token(token);
        free(str);
    }
    return 0;
}