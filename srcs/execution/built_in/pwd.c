/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:28:51 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/19 20:45:51 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

///@brief problem 

void	ft_pwd(t_env *env)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (path != NULL)
	{
		printf("the path  from get cwd is : %s\n", path);
		free(path);
		return ;
	}else {
		path = ft_getenv(env, "PWD");
		printf("the path  from my env is : %s\n", path);
		return ;
	}	
	// printf("%s\n", path);
}

