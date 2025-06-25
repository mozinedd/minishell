#include "minishell.h"

char	*get_env_value(char *varname, t_environment *envp)
{
	t_environment	*tmp;

	tmp = envp;
	while (tmp)
	{
		if (tmp->key
			&& ft_strncmp(tmp->key, varname, ft_strlen(varname)) == 0
			&& ft_strlen(tmp->key) == ft_strlen(varname))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}
int	ft_isdigit(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
char	*allocate_name_var(char *wrd, int *i)
{
	int		start;
	char	*varname;

	start = *i;
	if (ft_isdigit(wrd[*i]))
	{
		(*i)++;
		return (ft_strdup("0"));
	}
	while (ft_isalnum(wrd[*i]) || wrd[*i] == '_')
		(*i)++;
	varname = ft_substr(wrd, start, (*i) - start);
	return (varname);
}

char *replace_word(char *word, int start, int end, char *replace)
{
    char *new;
    int i = 0, j = 0, k = 0;

    if (!word || start < 0 || end < start || end > (int)ft_strlen(word))
        return (word);
    if (!replace)
        replace = "";
    new = malloc(ft_strlen(word) - (end - start) + ft_strlen(replace) + 1);
    if (!new)
        return (free(word), NULL);
    while (i < start)
        new[j++] = word[i++];
    while (replace[k])
        new[j++] = replace[k++];
    i = end + 1;
    while (word[i])
        new[j++] = word[i++];
    new[j] = '\0';
    return (new);
}
char *replace_quts(char *val)
{
    char *new_val;
    int i;

    if (!val)
        return (ft_strdup(""));
    new_val = ft_strdup(val);
    if (!new_val)
        return (NULL);
    i = 0;
    while (new_val[i])
    {
        if (new_val[i] == '\'')
            new_val[i] = 5;
        if (new_val[i] == '\"')
            new_val[i] = 6;
        i++;
    }
    return (new_val);
}
char	*expand_from_to(char *word, int start, int *end, t_environment *envp)
{
	int		i;
	char	*var;
	char	*value;
	int		dollar_sign;

	i = start;
	while (i < *end)
	{
		if (word[i] == '$')
		{
			dollar_sign = i++;
			var = allocate_name_var(word, &i);
			value = get_env_value(var, envp);
			if (!value)
				value = ft_strdup("");
			value = replace_quts(value);
			*end += ft_strlen(value) - ft_strlen(var) - 1;
			free(var);
			word = replace_word(word, dollar_sign, i - 1, value);
			i = ft_strlen(value) + dollar_sign - 1;
			free(value);
		}
		i++;
	}
	return (word);
}

char	*expan_word(char *wrd, t_environment *envp)
{
	int	i;
	int	k;

	i = 0;
	while (wrd[i])
	{
		if (wrd[i] == '\'' || wrd[i] == '\"')
		{
			if (wrd[i] == '\'')
			{
				skip_to_next(wrd, &i);
				continue ;
			}
			k = i;
			skip_to_next(wrd, &k);
			wrd = expand_from_to(wrd, i, &k, envp);
			i = k;
		}
		k = i;
		while (wrd[i] && wrd[i] != '\'' && wrd[i] != '\"')
			i++;
		wrd = expand_from_to(wrd, k, &i, envp);
	}
	return (wrd);
}

int expand_var(t_file *file, t_environment *envp)
{
    int i = 0;
    while (file[i].value)
    {
        if (file[i].type != HERDOC)
        {
            char *expanded_value = expan_word(file[i].value, envp);
            if (!expanded_value)
                return (0);
            //free(file[i].value);
            file[i].value = expanded_value;
        }
        i++;
    }
    return (1);
}
