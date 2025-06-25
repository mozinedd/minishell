
#include "minishell.h"

int g_sig_hander;

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}

int	no_op_in_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '>' || line[i] == '<' || line[i] == '|')
			return (0);
		i++;
	}
	return (1);
}

char	*read_command_line(void)
{
	char	*line;
	int		i;

	g_sig_hander = 1;
	line = readline("minishell$ ");
	g_sig_hander = 0;
	if (!line)
		return (NULL);
	if (no_op_in_line(line))
	{
		i = 0;
		while (line[i] && is_space(line[i]))
			i++;
		if (ft_strncmp(&line[i], "minishell", 10) == 0)
			return (line);
	}
	add_history(line);
	return (line);
}

void	skip_to_next(char *str, int *i)
{
	char	quote;

	quote = str[*i];
	(*i)++;
	while (str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if (str[*i])
		(*i)++;
}
