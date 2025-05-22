/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:17 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/08 18:59:52 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
int is_operator(char c)
{
    return (c == '>' || c == '<' || c == '|');
}
int no_op_in_line(char *line)
{
	int i = 0;
	while(line[i])
	{
		if(line[i] == '>' || line[i] == '<' | line[i] == '|')
			return 0;
		i++;
	}
	return 1;
}
char *read_command_line()
{
    char *line;
    int i;
    line = readline("minishell$ ");

    if(!line)
    {
        return NULL;
    }
	if(no_op_in_line(line))
	{
        i = 0;
		while(line[i] && is_space(line[i]))
			i++;
		if(ft_strncmp(&line[i], "minishell", 10) == 0)
			return line;
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

