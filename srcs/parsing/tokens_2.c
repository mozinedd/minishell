/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:55:31 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:55:32 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_word(char *line, int *i, t_tokens **token)
{
	int			start;
	char		*substr;
	t_tokens	*new;

	start = *i;
	while (1)
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			skip_to_next(line, i);
			continue ;
		}
		if (line[*i] == '\0' || is_space(line[*i]) || is_operator(line[*i]))
			break ;
		(*i)++;
	}
	substr = ft_substr(line, start, *i - start);
	if (!substr)
		return (0);
	new = new_token(substr, WORD);
	if (!new)
		return (0);
	add_token(token, new);
	return (1);
}

t_tokens	*tokenize_cmd(char *line)
{
	t_tokens	*token;
	int			i;

	token = NULL;
	i = 0;
	while (line[i])
	{
		if (is_space(line[i]))
			i++;
		else if (is_operator(line[i]))
			handl_op(line, &i, &token);
		else if (!handle_word(line, &i, &token))
			return (NULL);
	}
	return (token);
}

static int	append_with_pipe(t_tokens **all, t_tokens *tmp)
{
	t_tokens	*pipe;

	pipe = new_token(ft_strdup("|"), PIPE);
	if (!pipe)
		return (0);
	*all = append_token_list(*all, pipe);
	*all = append_token_list(*all, tmp);
	return (1);
}

t_tokens	*tokenize_all_segments(char **lines)
{
	t_tokens	*all_tokens;
	t_tokens	*tmp;
	int			i;

	all_tokens = NULL;
	i = 0;
	while (lines[i])
	{
		tmp = tokenize_cmd(lines[i]);
		if (!tmp)
			return (NULL);
		if (!all_tokens)
			all_tokens = tmp;
		else if (!append_with_pipe(&all_tokens, tmp))
			return (NULL);
		i++;
	}
	return (all_tokens);
}
