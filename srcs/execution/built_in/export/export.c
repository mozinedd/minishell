/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:28:56 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/12 20:20:47 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_valid_key(char *key)
{
	int i;

	if (!ft_isalpha(key[0]) || key[0] == '_')
	{
		printf("minishell: export: %s: not a valid identifier\n", key);
		// exit status
		return (0);
	}
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) || key[i] == '_')
		{
			printf("minishell: export: %s: not a valid identifier\n", key);
			return (0);
		}
		i++; 
	} 
	return (1);
}

char **split_key_value(char *cmd, int *is_append)
{
	char **final_resutl;
	char *result = NULL;
	int key_len = 0;

	result = ft_strchr(cmd, '=');
	final_resutl = gc_malloc(sizeof(char *) * 3);
	if (result)
	{
		if (cmd[0] == '=')
			return (printf("invalid identifier '%s'\n", cmd), NULL);
		if (*(result - 1) == '+')
			*is_append = 1;
		if (!final_resutl)
			return NULL;
		if (*is_append)
		{
			key_len = result - cmd - 1;
			final_resutl[0] =  ft_substr(cmd, 0, key_len);
			final_resutl[1] = ft_strdup(result + 1);
			final_resutl[2] = NULL;
		}
		else 
		{
			key_len = result - cmd ;
			final_resutl[0] =  ft_substr(cmd, 0, key_len);
			final_resutl[1] = ft_strdup(result + 1);
			final_resutl[2] = NULL;
		}
	}
	else
	{
		final_resutl[0] = ft_strdup(cmd);
		final_resutl[1] = NULL;
	}
	return final_resutl;
}






void	ft_export (t_env **env, char **cmd)
{
	char **my_key_value;
	int	is_append = 0;
	t_env *curr = *env;

	int i = 1;
	if (!cmd[1])
	{
		if(!*env)
			return ;
		return (print_exported_vars(*env));
	}

	while (cmd[i])
	{
		my_key_value = split_key_value(cmd[i], &is_append);
		if (!my_key_value || !is_valid_key(my_key_value[0]))
		{
			exit_status(1, 0);
			printf("the exit status is : %d\n", exit_status(0, 1));
			return ; 
		}
		curr = is_exist(*env, my_key_value[0]);
		if(curr){
			update_value(&curr, my_key_value[1], is_append);
			printf("hi from curr apend\n");
		}
		else
		{
			printf("haneasldkjf;ldasfj \n");
			add_var_env(env, my_key_value[0], my_key_value[1], cmd[i]);
		}
		i++;
	}
	return ;
}
