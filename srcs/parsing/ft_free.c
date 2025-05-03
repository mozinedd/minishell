/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:22 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/03 22:26:43 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

// libere tous les tokens
void free_token(t_tokens *token)
{
	t_tokens *tmp;

	while(token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}

void free_commands(t_commands *commands)
{
    t_commands *tmp;

    while (commands)
    {
        tmp = commands;
        commands = commands->next;

        if (tmp->cmd)
        {
            char **cmd = tmp->cmd;
            while (*cmd)
            {
                free(*cmd);
                cmd++;
            }
            free(tmp->cmd);
        }

        if (tmp->file)
        {
            t_file *file = tmp->file;
            while (file->type != 0)
            {
                free(file->value);
                file++;
            }
            free(tmp->file);
        }

        free(tmp);
    }
}
