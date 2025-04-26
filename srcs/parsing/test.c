#include "test.h"
static int is_operator(char c)
{
    return (c == '>' || c == '<' || c == '|');
}
char *read_command_line()
{
    char *line;

    line = readline("minishell$ ");

    if(!line)
    {
        return NULL;
    }
    add_history(line);
    return line;
}
int count_op(char *str)
{
    int count = 0;
    while (*str)
    {
        if(is_operator(*str))
        {
            count = count + 2;
        }
        str++;
    }
    return count;
}
int ft_strlen(char *str)
{
    int i = 0;


    while(str[i])
        i++;
    return i;
}

int is_valid_line(char *line)
{
    int i = 0;
    while (line[i] == ' ')
        i++;
    if (is_operator(line[i]))
        return 0;
    int len = ft_strlen(line) - 1;
    if (is_operator(line[len]))
        return 0;
    return 1;
}

char **split_arg(char *line)
{
    char *new_line;
    char **split_line;
    int i = 0;
    int j = 0;


    new_line = malloc(sizeof(char) * (ft_strlen(line) + count_op(line) + 1));
    if (!new_line)
        return NULL;
    while (line[i])
    {
        if (is_operator(line[i]))
        {
            if (j == 0 || new_line[j-1] != ' ')
                new_line[j++] = ' ';

            new_line[j++] = line[i];
            if (line[i+1] == '|')
            {
                free(new_line);
                return NULL;
            }
            if (line[i+1] == '>' || line[i+1] == '<')
                new_line[j++] = line[++i];
            if(line[i+1] == '>' || line[i+1] == '<')
            {
                free(new_line);
                return NULL;
            }  
            if (line[i+1] != ' ')
                new_line[j++] = ' ';

            i++;
        }
        else
        {
            new_line[j++] = line[i++];
        }
    }
    new_line[j] = '\0';

    split_line = ft_split(new_line, ' ');
    free(new_line);
    return split_line;
}
void f()
{
    char cmd[50];
    sprintf(cmd, "leaks %d", getpid());
    system(cmd);
}
int main(void)
{
    char *str = read_command_line();
    char **result;
    int i = 0;
    atexit(f);
    if (!is_valid_line(str))
    {
        printf("Syntax error: line cannot start or end with an operator.\n");
        free(str);
        return (1);
    }
    result = split_arg(str);
    if (!result)
    {
        printf("Allocation failed.\n");
        free(str);
        return (1);
    }
    while (result[i])
    {
        printf("Word %d: %s\n", i, result[i]);
        i++;
    }
    i = 0;
    while (result[i])
    {
        free(result[i]);
        i++;
    }
    free(result);
    free(str);
    return (0);
}


