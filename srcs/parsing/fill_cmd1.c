/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:33:38 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:58:28 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_word(char *str, char *new)
{
	char	*tmp_str;

	if (!str)
		return (ft_strdup(new));
	tmp_str = ft_strjoin2(str, " ");
	free(str);
	if (!tmp_str)
		return (NULL);
	str = ft_strjoin2(tmp_str, new);
	free(tmp_str);
	return (str);
}

static char	*join_expanded_word(char *str, t_tokens *tmp, t_glob *global)
{
	char	*expanded;

	expanded = expan_word(tmp->str, global);
	if (!expanded)
		return (str);
	str = join_word(str, expanded);
	return (str);
}

char	*join_commands(t_glob *global)
{
	t_tokens	*tmp;
	char		*str;
	int			is_red;

	if (!global || !global->token)
		return (NULL);
	is_red = 0;
	str = NULL;
	tmp = global->token;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redirection(tmp))
			is_red = 1;
		else if (tmp->type == WORD && is_red == 1)
			is_red = 0;
		else if (tmp->type == WORD && is_red == 0)
		{
			str = join_expanded_word(str, tmp, global);
			if (!str)
				return (NULL);
		}
		tmp = tmp->next;
	}
	global->token = tmp;
	return (str);
}

void	counter(const char *expanded_word, int *i, int *count)
{
	while (expanded_word[*i])
	{
		if (is_space(expanded_word[*i]))
		{
			(*i)++;
			continue ;
		}
		while (1)
		{
			if (expanded_word[*i] == '\'' || expanded_word[*i] == '"')
			{
				skip_to_next((char *)expanded_word, i);
				continue ;
			}
			if (expanded_word[*i] == '\0' || is_space(expanded_word[*i]))
				break ;
			(*i)++;
		}
		(*count)++;
	}
}

int	size_cmd(char *expanded_word)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	if (!expanded_word)
		return (0);
	counter(expanded_word, &i, &count);
	return (count);
}
