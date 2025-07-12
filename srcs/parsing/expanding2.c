#include "minishell.h"

static int is_special_quote_case(char *w, int i, t_glob *g)
{
	if (!g->in_double_quotes && w[i] == '$' && (w[i + 1] == '\'' || w[i + 1] == '"'))
		return (1);
	return (0);
}

static char *handle_exit_code(char *w, int *i, int *end, t_glob *g)
{
	char *value;
	int pos;

	value = ft_itoa(exit_status(g->exit_status, 1));
	pos = *i;
	if (!value)
		return (NULL);
	*end += ft_strlen(value) - 2;
	w = replace_word(w, pos, pos + 1, value);
	*i = pos + ft_strlen(value);
	// free(value);
	return (w);
}

static char *handle_variable(char *w, int *i, int *end, t_glob *g)
{
	int pos;
	char *var;
	char *val;

	pos = (*i)++;
	var = allocate_name_var(w, i);
	if (!var)
		return (NULL);
	val = get_env_value(var, g->env);
	if (!val)
		val = ft_strdup("");
	val = replace_quts(val);
	*end += ft_strlen(val) - ft_strlen(var) - 1;
	// free(var);
	w = replace_word(w, pos, *i - 1, val);
	*i = pos + ft_strlen(val);
	// free(val);
	return (w);
}

static char *expand_loop(char *word, int *i, int *end, t_glob *g)
{
	if (is_special_quote_case(word, *i, g))
	{
		word = replace_word(word, *i, *i, "");
		(*end)--;
		(*i)++;
		return (word);
	}
	if (word[*i] == '$' && word[*i + 1] && word[*i + 1] != '\'' && word[*i + 1] != '"')
	{
		if (word[*i + 1] == '?')
			word = handle_exit_code(word, i, end, g);
		else
			word = handle_variable(word, i, end, g);
	}
	else
		(*i)++;
	return (word);
}

char *herdoc_expand(char *word, int start, int *end, t_glob *g)
{
	int i;

	if (!word || !end || !g)
		return (word);
	i = start;
	while (i < *end && word[i])
	{
		if (word[i] == '$' && !ft_isalnum(word[i + 1])&& word[i + 1] != '$'  && word[i + 1] != '?')
			i++;
		else
			word = expand_loop(word, &i, end, g);
	}
	return (word);
}
char *expand_from_to(char *word, int start, int *end, t_glob *g)
{
	int i;

	if (!word || !end || !g)
		return (word);
	i = start;
	while (i < *end && word[i])
		word = expand_loop(word, &i, end, g);
	return (word);
}
