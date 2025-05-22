#include "../../includes/minishell.h"

int main (int argc, char ** argv , char **env)
{
    t_environment *evnp;
    t_environment *current;
    (void)argv;
    (void)argc;
    evnp = list_of_env(env);
    current = evnp;
    while (current)
    {
        printf("%s=%s\n", current->key, current->value);
        current = current->next;
    }
}