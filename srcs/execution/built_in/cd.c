/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:29:19 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/07 18:52:20 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_cd(t_env *env, char **args)
{
	char *path;
	
	t_env *curr= env; 
	while(curr)
	{
		printf("the key is : %s\n", curr->key);
		curr = curr->next;
	}

	if (!args[1])
	{
		path = ft_getenv(env, "HOME");
		printf("the path is : %s\n", path);
		if (!path)
		{
			fprintf(stderr, "cd: HOME not set\n");
			return (1);
		}
	}
	else if (args[1])
		path = args[1];
	else if (args[1][0] == '~' || args[1][0] == '-')
	{
		fprintf(stderr, "cd : unsupported path format\n");
		return (1);
	}
	if (chdir(path) != 0)
	{
		perror("cd: no such file or directory\n");
		return (1);
	}
	return (0);
}
