/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sp_pipe2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:24:14 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:24:18 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	skip_until_pipe(char *line, int *i)
{
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '\"')
		{
			skip_to_next(line, i);
			continue ;
		}
		if (line[*i] == '|')
			break ;
		(*i)++;
	}
}

static int	split_one_cmd(char *line, char **res, int *i, size_t idx)
{
	int		start;
	char	*tmp;

	start = *i;
	skip_until_pipe(line, i);
	tmp = ft_substr(line, start, *i - start);
	if (!tmp)
		return (0);
	res[idx] = trim_spaces(tmp);
	if (!res[idx])
		return (0);
	if (line[*i] == '|')
		(*i)++;
	return (1);
}

static char	**split_by_p(char *line, size_t count)
{
	char	**res;
	size_t	idx;
	int		i;

	res = gc_malloc(sizeof(char *) * (count + 1));
	if (!res)
		return (0);
	idx = 0;
	i = 0;
	while (line[i] && idx < count)
	{
		if (!split_one_cmd(line, res, &i, idx))
			return (NULL);
		idx++;
	}
	res[idx] = NULL;
	return (res);
}

char	**split_by_pipes(char *line)
{
	size_t	count;

	if (!line)
		return (NULL);
	count = count_pipes(line);
	return (split_by_p(line, count));
}
