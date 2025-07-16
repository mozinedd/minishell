#include "minishell.h"
t_gc **get_garbage_collector(void)
{
    static t_gc *collector;
    return (&collector);
}

void *gc_malloc(size_t size)
{
    void        *allocated_ptr;
    t_gc  *new_node;

    if (size == 0)
        return (NULL);
    allocated_ptr = malloc(size);
    if (!allocated_ptr)
        return (NULL);
    new_node = malloc(sizeof(t_gc));
    if (!new_node)
        return (NULL);
    new_node->ptr = allocated_ptr;
    new_node->next = *get_garbage_collector();
    *get_garbage_collector() = new_node;
    return (allocated_ptr);
}
