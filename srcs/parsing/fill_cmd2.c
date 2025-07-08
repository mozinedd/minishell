#include "minishell.h"

void	add_str(char *joined_str, int *i)
{
	while (1)
	{
		if (joined_str[*i] == '\'' || joined_str[*i] == '"')
		{
			skip_to_next(joined_str, i);
			continue ;
		}
		if (joined_str[*i] == '\0' || is_space(joined_str[*i]))
			break ;
		(*i)++;
	}
}

static int	fill_cmd_array(char *joined_str, char **cmd)
{
	int		i;
	int		j;
	int		start;

	i = 0;
	j = 0;
	while (joined_str && joined_str[i])
	{
		if (is_space(joined_str[i]))
		{
			i++;
			continue ;
		}
		start = i;
		add_str(joined_str, &i);
		cmd[j++] = ft_substr(joined_str, start, i - start);
	}
	cmd[j] = NULL;
	return (1);
}

char	**fill_command(char *joined_str)
{
	char	**cmd;

	if (!joined_str)
		return (NULL);
	cmd = malloc(sizeof(char *) * (size_cmd(joined_str) + 1));
	if (!cmd)
		return (NULL);
	if (!fill_cmd_array(joined_str, cmd))
		return (NULL);
	return (cmd);
}
