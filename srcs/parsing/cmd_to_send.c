/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_to_send.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:04 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/03 23:31:14 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_commands *init_command(t_tokens *token)
{
    t_commands *command;
    t_tokens *tmp;
    int count = 0;

    tmp = token;
    while (tmp)
    {
        if (tmp->type == PIPE)
            count++;
        tmp = tmp->next;
    }
    command = malloc(sizeof(t_commands) * (count + 2));
    if(!command)
        return NULL;
    printf("\n iniy_command \n");
    return command;
}

t_file *init_files_of_commands(t_tokens *token)
{
    t_file *file;
    int count = 0;
    t_tokens *start = token;


    while (token && (token)->type != PIPE)
    {
        if (is_redirection(token))
            count++;
        token = (token)->next;
    }

    token = start;
    file  = malloc(sizeof(t_file) * (count + 1));
    if(!file)
        return NULL;
    printf("\n init_files_of_commands \n");
    return file;
}

int fill_files(t_file *files, t_tokens **token)
{
    int i = 0;

    while (*token && (*token)->type != PIPE)
    {
        if (is_redirection(*token))
        {
            files[i].type = (*token)->type;
            if((*token)->next && (*token)->next->type == WORD)
            {
                files[i].value = ft_strdup((*token)->next->str);
                if(!files[i].value)
                    return 0;
                i++;
                *token = (*token)->next;
            }
            else
            {
                write(1, "error in command\n", 18);
                return 0;
            }
        }
        *token = (*token)->next;
    }
    printf("\n fill_files \n");
    files[i].type = 0;
    files[i].value = NULL;
    return 1;
}

t_commands *init_command_node()
{
    t_commands *command = malloc(sizeof(t_commands));
    if (!command)
        return NULL;
    command->cmd = NULL;
    command->file = NULL;
    command->next = NULL;
    return command;
}

t_commands *create_commands(t_tokens *token)
{
    t_commands *head = NULL;
    t_commands *current = NULL;

    while (token)
    {
        t_commands *new_node = init_command_node();
        if (!new_node)
        {
            free_commands(head);
            return NULL;
        }
        new_node->file = init_files_of_commands(token);
        if (!new_node->file)
        {
            free_commands(head);
            return NULL;
        }
        if (!fill_files(new_node->file, &token))
        {
            free_commands(head);
            return NULL;
        }
        if (!head)
            head = new_node;
        else
            current->next = new_node;
        current = new_node;
        if (token && token->type == PIPE)
            token = token->next;
    }
    return head;
}


