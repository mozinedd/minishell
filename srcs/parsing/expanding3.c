/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:55:50 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 21:55:55 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_from_to(char *word, int start, int *end, t_glob *g)
{
	int	i;

	if (!word || !end || !g)
		return (word);
	i = start;
	while (i < *end && word[i])
		word = expand_loop(word, &i, end, g);
	return (word);
}

static char	*process_quoted_section(char *wrd, int *i, t_glob *global)
{
	int	k;

	k = *i;
	skip_to_next(wrd, &k);
	if (wrd[*i] == '\'')
	{
		*i = k;
		return (wrd);
	}
	global->in_double_quotes = 1;
	wrd = expand_from_to(wrd, *i + 1, &k, global);
	global->in_double_quotes = 0;
	*i = k;
	return (wrd);
}

static char	*process_unquoted_section(char *wrd, int *i, t_glob *global)
{
	int	k;

	k = *i;
	while (wrd[*i] && wrd[*i] != '\'' && wrd[*i] != '\"')
		(*i)++;
	wrd = expand_from_to(wrd, k, i, global);
	return (wrd);
}

char	*expan_word(char *wrd, t_glob *global)
{
	int	i;

	if (!wrd || !global)
		return (wrd);
	i = 0;
	while (wrd[i])
	{
		if (wrd[i] == '\'' || wrd[i] == '\"')
		{
			wrd = process_quoted_section(wrd, &i, global);
			if (!wrd)
				return (NULL);
		}
		else
		{
			wrd = process_unquoted_section(wrd, &i, global);
			if (!wrd)
				return (NULL);
		}
	}
	return (wrd);
}

int	expand_var(t_file *file, t_glob *global)
{
	int		i;
	char	*expanded_value;

	if (!file || !global)
		return (0);
	i = 0;
	while (file[i].value)
	{
		if (file[i].type != HERDOC)
		{
			expanded_value = expan_word(file[i].value, global);
			if (!expanded_value)
				return (0);
			file[i].value = expanded_value;
		}
		i++;
	}
	return (1);
}
