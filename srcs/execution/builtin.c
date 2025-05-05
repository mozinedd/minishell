#include "minishell.h"



int cd_builtin(char **args)
{
    if (!args[1]) {
        fprintf(stderr, "cd: path to change directory\n");
        return 1;
    }
    if (chdir(args[1]) != 0) {
        perror("cd: no such file or directory\n");
    }

    return 1;
}