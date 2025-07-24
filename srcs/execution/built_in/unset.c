/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:28:45 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/24 15:13:42 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_key(t_env **env, char *key)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, key) == 0)
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			break ;
		}
		prev = curr;
		curr = curr->next;
	}
}

static int	is_valid_key(char *key, int *status)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
	{
		*status = 1;
		printf("minishell: unset: %s: not a valid identifier\n", key);
		return (0);
	}
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
		{
			*status = 1;
			printf("minishell: unset: %s: not a valid identifier\n", key);
			return (0);
		}
		i++;
	}
	return (1);
}

int	ft_unset(char **args, t_env **env)
{
	int	i;
	int	status;

	status = 0;
	i = 1;
	while (args[i])
	{
		if (is_valid_key(args[i], &status))
			remove_key(env, args[i]);
		i++;
	}
	exit_status(status, 0);
	return (0);
}
