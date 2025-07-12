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
		// free(trimmed);
		exit_status(258, 0);
		return (NULL);
	}
	if (!valid_quotes(trimmed))
	{
		write(2, "msh: syntax error near unexpected token `quotes'\n", 50);
		// free(trimmed);
		exit_status(1, 0);
		return (NULL);
	}
	return (trimmed);
}

t_tokens	*lexer(char *line, t_glob *global)
{
	t_tokens	*tokens;
	char		**split_lines;
	char		*clean_line;

	clean_line = prepare_line(line);
	printf("2 - line : %s\n", clean_line);
	if (!clean_line)
		return (NULL);
	split_lines = split_by_pipes(clean_line);
	printf("3 - line : %s\n", split_lines[0]);
	// free(clean_line);
	if (!split_lines)
		return (NULL);
	split_lines = operate_export(split_lines);
	printf("4 - line : %s\n", split_lines[0]);
	if (!split_lines)
	{
		// free_split(split_lines);
		return (NULL);
	}
	tokens = tokenize_all_segments(split_lines);
	// free_split(split_lines);
	if (!tokens)
		return (NULL);
	global->token = tokens;
	return (tokens);
}
