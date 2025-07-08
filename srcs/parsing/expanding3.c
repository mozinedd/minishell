#include "minishell.h"

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
