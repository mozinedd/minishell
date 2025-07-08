#include "minishell.h"

bool	redir_error(t_glob *g)
{
	write(2, "msh : syntax error near unexpected token `newline'\n", 52);
	g->exit_status = 258;
	return (false);
}

bool	pipe_error(t_glob *g)
{
	write(2, "msh :syntax error near unexpected token `|'\n", 45);
	g->exit_status = 258;
	return (false);
}

bool	check_redirections(t_tokens *t, t_glob *g)
{
	while (t)
	{
		if (is_redirection(t))
		{
			t = t->next;
			if (!t || t->type != WORD)
				return (redir_error(g));
		}
		t = t->next;
	}
	return (true);
}

bool	check_pipe_error(char *line, t_glob *g)
{
	int	i;

	i = 0;
	while (line[i] && is_space(line[i]))
		i++;
	if (line[i] == '|')
		return (pipe_error(g), false);
	while (line[i])
	{
		if (line[i] == '|')
		{
			i++;
			while (line[i] && is_space(line[i]))
				i++;
			if (line[i] == '|' || line[i] == '\0')
				return (pipe_error(g), false);
		}
		else
			i++;
	}
	return (true);
}
