/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:28:45 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 16:09:14 by mozinedd         ###   ########.fr       */
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

int	ft_unset(char **args, t_env **env)
{
	int	i;

	i = 1;
	while (args[i])
	{
		remove_key(env, args[i]);
		i++;
	}
	return (0);
}
