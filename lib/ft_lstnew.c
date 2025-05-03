#include "../includes/minishell.h"

t_environment	*ft_lstnew(void *content)
{
	t_environment	*lst;

	lst = malloc(sizeof(t_environment));
	if (!lst)
		return (NULL);
	lst->value = content;
	lst->next = NULL;
	return (lst);
}