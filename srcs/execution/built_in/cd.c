/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:19 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 16:04:20 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_old_pwd(t_env **env, char *oldpwd)
{
	t_env	*curr;
	char	**cmd;

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
		if (curr == NULL)
		{
			cmd = gc_malloc(sizeof(char *) * 2);
			cmd[0] = "export";
			cmd[1] = ft_strjoin("OLDPWD=", oldpwd);
			cmd[2] = NULL;
			ft_export(env, cmd);
		}
	}
}

void	add_to_pwd(t_env **env, char *arg)
{
	char	*oldpwd;
	t_env	*curr;

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
	if (oldpwd != NULL)
		update_old_pwd(env, oldpwd);
}

void	long_print(void)
{
	ft_printf("cd: error retrieving current"
		"directory: getcwd: cannot access parent"
		"directories: No such file or directory\n");
}

void	cwd_valid(char *cwd_return, t_env *env)
{
	char	*oldpwd;
	char	**cmd;
	t_env	*curr;

	curr = env;
	oldpwd = NULL;
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
	if (curr == NULL)
	{
		cmd = gc_malloc(sizeof(char *) * 2);
		cmd[0] = "export";
		cmd[1] = ft_strjoin("PWD=", cwd_return);
		cmd[2] = NULL;
		ft_export(&env, cmd);
	}
	update_old_pwd(&env, oldpwd);
}

int	ft_cd(t_env *env, char **args)
{
	char	*path;
	char	*cwd;
	char	cwd_return[4096];

	if (!args[1])
	{
		path = ft_getenv(env, "HOME");
		if (!path)
			return (ft_printf("cd: HOME not set\n", 1), exit_status(1, 0));
	}
	else if (args[1])
		path = args[1];
	if (chdir(path) != 0)
		return (perror("cd"), exit_status(1, 0), 1);
	cwd = getcwd(cwd_return, sizeof(cwd_return));
	if (!cwd)
		return (long_print(), add_to_pwd(&env, args[1]), 1);
	else
		cwd_valid(cwd_return, env);
	return (exit_status(1, 0), 1);
}
