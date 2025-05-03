#include "../../includes/minishell.h"

t_environment *creat_node(char *env)
{
		size_t          key_lent;
		t_environment   *new_node;
		char            *equal;

		new_node = malloc(sizeof(t_environment));
		if (!new_node)
			return (NULL);
		equal = ft_strchr(env, '=');
		if (!equal)
				return (NULL);
		key_lent = equal - env;
		new_node->key = ft_strndup(env, key_lent);
		new_node->value = ft_strdup(equal + 1);
		if (!new_node->key || !new_node->value)
		{
				free(new_node->key);
				free(new_node->value);
				free(new_node);
				return (NULL);
		}
		new_node->next = NULL;
		return (new_node);
}

t_environment *list_of_env(char **env)
{
	t_environment *list;
	t_environment *size;
	t_environment *new_node;
	int i;

	list = NULL;
	size = NULL;
	i = 0;
	while (env[i])
	{
		new_node = creat_node(env[i]);
		if (!new_node)
		{
			i++;
			continue;
		}
		if (!list)
		{
			list = new_node;
			size = new_node;
		}
		 else
		{
			size->next = new_node;
			size = new_node;
		}
		i++;
	}
	return(list);
}