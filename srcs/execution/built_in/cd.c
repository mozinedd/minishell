/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:19 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/15 16:07:56 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///@b custimse cd norminette : handle env -i :

void	update_old_pwd(t_env **env, char *oldpwd)
{
	t_env	*curr;
	
	curr = *env;
	if (oldpwd != NULL)
	{
		while (curr)
		{
			if (ft_strcmp(curr->key, "OLDPWD") == 0)
			{
				curr->value = oldpwd;
				break ;
			}
			curr = curr->next;
		}
	}
}

void	add_to_pwd(t_env **env, char *arg){

	char *oldpwd;
	t_env *curr;


	curr = *env;
	oldpwd = NULL;
	while (curr)
	{
		if (ft_strcmp(curr->key, "PWD") == 0)
		{
			oldpwd = curr->value;
			curr->value = ft_strjoin(curr->value, "/");
			curr->value = ft_strjoin(curr->value, arg);
			break ;
		}
		curr = curr->next;
	}
	update_old_pwd(env, oldpwd);
}

int	ft_cd(t_env *env, char **args)
{
	char	*path;
	char	*cwd;
	char	*oldpwd =NULL ;
	char	cwd_return[4096];

	if (!args[1])
	{
		path = ft_getenv(env, "HOME");
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	else if (args[1])
		path = args[1];
	/// @brief OPTIONAL
	else if (args[1][0] == '~' || args[1][0] == '-')
	{
		fprintf(stderr, "cd : unsupported path format\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd");
		return (1);
	}
	/// handle updating pwd and oldpwd
	cwd = getcwd(cwd_return, sizeof(cwd_return));
	if (!cwd)
	{
		ft_printf("cd: error retrieving current" 
		"directory: getcwd: cannot access parent"
		"directories: No such file or directory\n");
		add_to_pwd(&env, args[1]);
		return 1;
	}
	else 
	{
		t_env *curr = env;
		while (curr)
		{
			if (ft_strcmp(curr->key, "PWD") == 0)
			{
				oldpwd = curr->value;
				curr->value = ft_strdup(cwd_return);
				break ;
			}
			curr = curr->next;
		}
		update_old_pwd(&env, oldpwd);
	}
	
	return (exit_status(1, 0), 1);
}
