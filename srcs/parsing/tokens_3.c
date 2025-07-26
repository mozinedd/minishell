/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:56:33 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/26 12:48:12 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prepare_line(char *line)
{
	char	*trimmed;

	if (!line || !*line)
		return (NULL);
	trimmed = ft_strtrim(line, " \t\n\r\v\f");
	free(line);
	if (!trimmed)
		return (NULL);
	if (!check_pipe_error(trimmed))
	{
		exit_status(258, 0);
		return (NULL);
	}
	if (!valid_quotes(trimmed))
	{
		write(2, "msh: syntax error near unexpected token `quotes'\n", 50);
		exit_status(258, 0);
		return (NULL);
	}
	return (trimmed);
}

t_tokens	*lexer(char *line, t_glob *global)
{
	t_tokens	*tokens;
	char		**split_lines;
	char		*clean_line;
	int			count;

	clean_line = prepare_line(line);
	if (!clean_line)
		return (NULL);
	split_lines = split_by_pipes(clean_line);
	if (!split_lines)
		return (NULL);
	split_lines = operate_export(split_lines);
	if (!split_lines)
		return (NULL);
	tokens = tokenize_all_segments(split_lines);
	if (!tokens)
		return (NULL);
	count = count_herdoc(tokens);
	if (count >= 17)
	{
		write(2, "maximum here-document count exceeded\n", 38);
		exit(2);
	}
	global->token = tokens;
	return (tokens);
}
