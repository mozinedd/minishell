/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:28:56 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/24 16:02:52 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *key, int *status)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		*status = 1;
		printf("minishell: export: %s: 1 not a valid identifier\n", key);
		return (0);
	}
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			*status = 1;
			printf("minishell: export: %s: 2 not a valid identifier\n", key);
			return (0);
		}
		i++;
	}
	return (1);
}

char	**init_final_reuslt(int is_append, char *result, char *cmd)
{
	int		key_len;
	char	**final_result;

	key_len = 0;
	final_result = gc_malloc(sizeof(char *) * 3);
	if (is_append)
	{
		key_len = result - cmd - 1;
		final_result[0] = ft_substr(cmd, 0, key_len);
		final_result[1] = ft_strdup(result + 1);
		final_result[2] = NULL;
	}
	else
	{
		key_len = result - cmd ;
		final_result[0] = ft_substr(cmd, 0, key_len);
		final_result[1] = ft_strdup(result + 1);
		final_result[2] = NULL;
	}
	return (final_result);
}

char	**split_key_value(char *cmd, int *is_append)
{
	char	**final_result;
	char	*result;

	result = ft_strchr(cmd, '=');
	if (result)
	{
		if (cmd[0] == '=')
			return (printf("invalid identifier '%s'\n", cmd), NULL);
		if (*(result - 1) == '+')
			*is_append = 1;
		final_result = init_final_reuslt(*is_append, result, cmd);
	}
	else
	{
		final_result = gc_malloc(sizeof(char *) * 2);
		final_result[0] = ft_strdup(cmd);
		final_result[1] = NULL;
	}
	return (final_result);
}

void	ft_export(t_env **env, char **cmd)
{
	char	**my_key_value;
	int		is_append;
	t_env	*curr;
	int		i;
	int		status;

	i = 1;
	status = 0;
	curr = *env;
	is_append = 0;
	if (!cmd[1])
		return (print_exported_vars(*env));
	while (cmd[i])
	{
		my_key_value = split_key_value(cmd[i], &is_append);
		if (!my_key_value || (!is_valid_key(my_key_value[0], &status) && i++))
			continue ;
		curr = is_exist(*env, my_key_value[0]);
		if (curr)
			update_value(&curr, my_key_value[1], is_append);
		else
			add_var_env(env, my_key_value[0], my_key_value[1], cmd[i]);
		i++;
	}
	exit_status(status, 0);
}
