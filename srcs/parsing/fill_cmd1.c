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

static char	*joint_expand(char *str, t_tokens *tmp, t_glob *global)
{
	char	*expanded;

	expanded = expan_word(tmp->str, global);
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
			str = joint_expand(str, tmp, global);
		tmp = tmp->next;
	}
	global->token = tmp;
	return (str);
}

void	counter(char *expanded_word, int *i, int *count)
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
				skip_to_next(expanded_word, i);
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
