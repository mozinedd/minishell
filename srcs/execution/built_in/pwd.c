/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/05 15:28:51 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/12 17:38:29 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env *env)
{
	char	*path;
	(void)env;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("error geting current working directory\n");
		return;
	}
	printf("%s\n", path);
}

