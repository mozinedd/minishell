/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_export.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 17:43:30 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 19:54:40 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exported_vars(t_env *env)
{
	if (!env)
		return ;
	while (env)
	{
		if (env->value)
			printf("declare -x %s=\"%s\"\n", env->key, env->value);
		else
			printf("declare -x %s\n", env->key);
		env = env->next;
	}
}

t_env	*creat_new_var(char *key, char *value, char *key_val)
{
	t_env	*new_node;

	new_node = gc_malloc (sizeof(t_env));
	if (!value)
	{
		new_node->key = ft_strdup(key);
		if (ft_strchr(key_val, '=') != NULL)
			new_node->value = ft_strdup("");
		else
			new_node->value = NULL;
		new_node->next = NULL;
	}
	else
	{
		new_node->key = ft_strdup(key);
		new_node->value = ft_strdup(value);
		new_node->next = NULL;
	}
	return (new_node);
}

void	add_var_env(t_env **env, char *key, char *value, char *key_val)
{
	t_env	*new_node;
	t_env	*current;

	new_node = creat_new_var(key, value, key_val);
	if (!new_node)
		return ;
	if (!*env)
	{
		*env = new_node;
		return ;
	}
	current = *env;
	while (current->next)
		current = current->next;
	current->next = new_node;
}

t_env	*is_exist(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	update_value(t_env **env, char *value, int is_append)
{
	char	*my_new_value;

	if (!env || !*env)
		return ;
	if (is_append)
	{
		if ((*env)->value)
			my_new_value = ft_strjoin((*env)->value, value);
		else
			my_new_value = ft_strdup(value);
		(*env)->value = my_new_value;
	}
	else
	{
		if (value == NULL)
			return ;
		(*env)->value = ft_strdup(value);
	}
}
