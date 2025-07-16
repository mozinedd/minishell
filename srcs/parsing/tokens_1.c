/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:54:38 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:54:39 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_tokens	*new_token(char *str, t_token_type type)
{
	t_tokens	*token;

	token = gc_malloc(sizeof(t_tokens));
	token->str = str;
	token->type = type;
	token->next = NULL;
	return (token);
}

void	add_token(t_tokens **token, t_tokens *new)
{
	t_tokens	*tmp;

	if (!*token)
	{
		*token = new;
		return ;
	}
	tmp = *token;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

void	handl_op(char *str, int *i, t_tokens **token)
{
	if (ft_strncmp(&str[*i], ">>", 2) == 0)
	{
		add_token(token, new_token(NULL, APPEND));
		*i += 2;
	}
	else if (ft_strncmp(&str[*i], "<<", 2) == 0)
	{
		add_token(token, new_token(NULL, HERDOC));
		*i += 2;
	}
	else if (str[*i] == '>')
	{
		add_token(token, new_token(NULL, REDIR_OUT));
		*i += 1;
	}
	else if (str[*i] == '<')
	{
		add_token(token, new_token(NULL, REDIR_IN));
		*i += 1;
	}
	else if (str[*i] == '|')
	{
		add_token(token, new_token(NULL, PIPE));
		*i += 1;
	}
}

t_tokens	*append_token_list(t_tokens *list1, t_tokens *list2)
{
	t_tokens	*tmp;

	if (!list1)
		return (list2);
	if (!list2)
		return (list1);
	tmp = list1;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = list2;
	return (list1);
}

int	valid_quotes(char *s)
{
	int		i;
	char	q;

	i = 0;
	while (s[i])
	{
		if (is_quote(s[i]))
		{
			q = s[i];
			i++;
			while (s[i] && s[i] != q)
				i++;
			if (s[i] == '\0')
				return (0);
		}
		i++;
	}
	return (1);
}
