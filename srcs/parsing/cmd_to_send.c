/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:04 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/03 17:33:12 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands *init_command(t_tokens *token)
{
    t_tokens *tmp;
    int count = 0;

    tmp = token;
    while(tmp)
    {
        if(tmp && tmp->type == PIPE)
            count++;
        tmp = tmp->next;
    }
    return (malloc(sizeof(t_commands) * (count + 2)));
}
t_file *init_files_of_commands(t_tokens **token)
{
    int count = 0;
    
    while(token && (*token)->type != PIPE)
    {
        if(is_redirection(*token))
            count++;
        (*token) = (*token)->next;
    }
    return(malloc(sizeof(t_file) * (count + 1)));
}
t_commands *creat_files_in_commands(t_tokens *token)
{
    t_tokens *tmp;
    t_commands *command;

    command = init_command(token);
    tmp = token;
    while(command)
    {
        command->file = init_command(&token);
        token = token->next;
        command = command->next;
    }
    token = tmp;
    
}




