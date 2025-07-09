#include "minishell.h"

void gc_free(void)
{
    t_gc    *current;
    t_gc    *next;

    current = *get_garbage_collector();
    while (current)
    {
        next = current->next;
        free(current->ptr);
        free(current);
        current = next;
    }
    *get_garbage_collector() = NULL;
}
