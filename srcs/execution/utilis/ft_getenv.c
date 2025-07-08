/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:18:47 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/07 18:43:16 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_getenv(t_env *env, const char *key)
{
	t_env	*curr = env;
	
	while(curr)
	{
		if (!ft_strcmp(curr->key, key))
			return curr->value;
		curr = curr->next;
	}
	return NULL;
}
