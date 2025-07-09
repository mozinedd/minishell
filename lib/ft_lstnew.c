#include "../includes/minishell.h"

t_env*ft_lstnew(void *content)
{
	t_env	*lst;

	lst = gc_malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->value = content;
	lst->next = NULL;
	return (lst);
}