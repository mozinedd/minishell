
#include "minishell.h"

char	*join_commands(t_tokens **token, t_environment *env)
{
	int			is_red;
	t_tokens	*tmp;
	char		*str;

	is_red = 0;
	str = NULL;
	tmp = *token;
	while (tmp && tmp->type != PIPE)
	{
		if (is_redirection(tmp))
			is_red = 1;
		else if (tmp->type == WORD && is_red == 1)
			is_red = 0;
		else if (tmp->type == WORD && is_red == 0)
		{
			str = ft_strjoin(str, " ");
			str = ft_strjoin(str, expan_word(tmp->str, env));
		}
		tmp = tmp->next;
	}
	*token = tmp;
	return (str);
}

int	size_cmd(char *expanded_word)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (expanded_word == NULL)
		return (0);
	while (expanded_word[i])
	{
		if (is_space(expanded_word[i]))
		{
			i++;
			continue;
		}
		else
		{
			while (1)
			{
				if (expanded_word[i] == '\'' || expanded_word[i] == '\"')
				{
					skip_to_next(expanded_word, &i);
					continue;
				}
				if (expanded_word[i] == '\0' || is_space(expanded_word[i]))
					break ;
				i++;
			}
			count++;
		}
	}
	return (count);
}

char	**fill_command(char *joined_str)
{
	int		i;
	int		j;
	int		start;
	char	**cmd;

	j = 0;
	cmd = malloc(sizeof(char *) * (size_cmd(joined_str) + 1));
	if (!cmd)
		return (NULL);
	i = 0;
	while (joined_str && joined_str[i])
	{
		if (is_space(joined_str[i]))
		{
			i++;
			continue ;
		}
		else
		{
			start = i;
			while (1)
			{
				if (joined_str[i] == '\'' || joined_str[i] == '\"')
				{
					skip_to_next(joined_str, &i);
					continue ;
				}
				if (joined_str[i] == '\0' || is_space(joined_str[i]))
					break ;
				i++;
			}
			cmd[j++] = ft_substr(joined_str, start, i - start);
		}
	}
	cmd[j] = NULL;
	return (cmd);
}
