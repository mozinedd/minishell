/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_of_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/13 18:00:11 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 16:36:32 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*creat_node(char *env)
{
	size_t	key_lent;
	t_env	*new_node;
	char	*equal;

	new_node = gc_malloc(sizeof(t_env));
	equal = ft_strchr(env, '=');
	if (!equal)
		return (NULL);
	key_lent = equal - env;
	new_node->key = ft_strndup(env, key_lent);
	new_node->value = ft_strdup(equal + 1);
	new_node->next = NULL;
	return (new_node);
}

t_env	*list_of_env(char **env)
{
	t_env	*list;
	t_env	*size;
	t_env	*new_node;
	int		i;

	(1) && (list = NULL, size = NULL, i = -1);
	if (!env || !*env)
		return (NULL);
	while (env[++i])
	{
		new_node = creat_node(env[i]);
		if (!new_node)
			continue ;
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
	}
	return (list);
}
