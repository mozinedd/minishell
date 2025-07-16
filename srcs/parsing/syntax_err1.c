/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_err1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:53:31 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:53:49 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	redir_error(void)
{
	write(2, "msh : syntax error near unexpected token `newline'\n",
		52);
	exit_status(258, 0);
	return (false);
}

bool	pipe_error(void)
{
	write(2, "msh :syntax error near unexpected token `|'\n",
		45);
	exit_status(258, 0);
	return (false);
}

bool	check_redirections(t_tokens *t)
{
	while (t)
	{
		if (is_redirection(t))
		{
			t = t->next;
			if (!t || t->type != WORD)
				return (redir_error());
		}
		t = t->next;
	}
	return (true);
}

bool	check_pipe_error(char *line)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '|')
		return (pipe_error(), false);
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] && is_space(line[i]))
				i++;
			if (line[i] == '|' || line[i] == '\0')
				return (pipe_error(), false);
		}
		else
			i++;
	}
	return (true);
}
