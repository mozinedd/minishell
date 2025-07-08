/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:49 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/03 16:23:50 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int is_redirection(t_tokens *type)
{
	return(type->type == APPEND || type->type == REDIR_IN
			|| type->type == REDIR_OUT || type->type == HERDOC);
}
bool	syntax_error(t_tokens **token)
{
	t_tokens *tmp;
	int i;
	
	tmp = *token;
	while(tmp)
	{
		if(is_redirection(tmp))
		{
			tmp = tmp->next;
			if(!tmp || tmp->type != WORD)
			{
				write(2, "syntax error redirection\n", ft_strlen("syntax error redirection\n"));
				return false;
			}
		}
		tmp = tmp->next;
	}
	tmp = *token;
	if(tmp->type == PIPE)
	{				
		write(2, "syntax error Pipe\n", 19);
		return false;		
	}
	while (tmp)
	{
		if(tmp->type == PIPE)
		{
			if(tmp->next == NULL || tmp ->next->type == PIPE)
			{
				write(2, "syntax error Pipe\n", ft_strlen("syntax error Pipe\n"));
				return false;
			}
		}
		tmp = tmp->next;
	}
	tmp = *token;
	while(tmp->next)
		tmp = tmp->next;
	i = 0;
	char quote;
	int index;
	while(tmp->str && tmp->str[i])
	{
		if(tmp->str[i] == '\'' || tmp->str[i] == '\"')
		{
			quote = tmp->str[i];
			index =i;
			skip_to_next(tmp->str, &i);
			if(!tmp->str[i] && (tmp->str[i - 1] != quote || index == i - 1))
			{
				write(2, "syntax error inclose quotes\n", 29);
				return false;				
			}
		}
		else
			i++;
	}
	return (true);
}
