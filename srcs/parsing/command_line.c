/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:17 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/03 16:23:18 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int is_operator(char c)
{
    return (c == '>' || c == '<' || c == '|');
}
char *read_command_line()
{
    char *line;

    line = readline("minishell$ ");

    if(!line)
    {
        return NULL;
    }
    add_history(line);
    return line;
}

void skip_to_next(char *str, int *i)
{
	char quote;
	quote = str[*i];
	(*i)++;
	while(str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if(str[*i])
		(*i)++;
}

