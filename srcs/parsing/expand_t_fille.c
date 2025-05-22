#include "minishell.h"

char *get_env_value(char *varname, t_environment *envp)
{
    t_environment *tmp;

    tmp = envp;
    while(tmp)
    {
        if(tmp->key && ft_strncmp(tmp->key, varname, ft_strlen(varname)) == 0 && ft_strlen(tmp->key) == ft_strlen(varname))
            return tmp->value;
        tmp = tmp->next;
    }
    return NULL;
}
char *allocate_name_var(char *wrd, int *i)

{
    int start = *i;
    char *varname;

    while(ft_isalnum(wrd[*i]) || wrd[*i] == '_')
        (*i)++;
    varname = ft_substr(wrd, start, (*i) - start);
    return varname;
}
char *replace_word(char *word, int start, int end, char *replace)
{
    char *new;
    int i = 0, j = 0, k;

    if (!replace)
        replace = "";
    if(start == end)
        return word;
    new = malloc(sizeof(char) * (ft_strlen(word) - (end - start) + ft_strlen(replace) + 1));
    if (!new)
        return (free(word), NULL);
    while (i < start)
        new[j++] = word[i++];
    k = 0;
    while (replace[k])
        new[j++] = replace[k++];
    i = end + 1;
    while (word[i])
        new[j++] = word[i++];
    new[j] = '\0';
    return new;
}
char *expand_from_to(char *word, int start, int *end, t_environment *envp)
{
    int i = start;
    int new_end;
    char *var;
    char *value;
    int dollar_sign;
    while(i < *end)
    {
        if(word[i] == '$')
        {
            dollar_sign = i++;
            var = allocate_name_var(word, &i);
             new_end = ft_strlen(var); 
            value = get_env_value(var, envp);
            if (!value)
                value = "";
            *end += ft_strlen(value) - ft_strlen(var) - 1;
            free(var);
            word = replace_word(word, dollar_sign, i - 1, value);
            i = ft_strlen(value) + dollar_sign - 1;
        }
        i++;
    }
    return word;
}
char *expan_word(char *wrd, t_environment *envp)
{
    int i = 0;
    int k;
    while(wrd[i])
    {
		if(wrd[i] == '\'' || wrd[i] == '\"')
		{
            if(wrd[i] == '\'')
            {
			    skip_to_next(wrd, &i);
                continue;
            }
            k = i;
            skip_to_next(wrd, &k);
            wrd =  expand_from_to(wrd, i, &k, envp);
            i = k;
		}
        k = i;
        while(wrd[i] && wrd[i] != '\'' && wrd[i] != '\"')
		    i++;
        wrd =  expand_from_to(wrd, k, &i, envp);
    }
    return wrd;
}
int expand_var(t_file *file, t_environment *envp)
{
    int i = 0;

    while (file[i].value)
    {
        if (file[i].type != HERDOC)
        {
            char *expanded_value = expan_word(file[i].value, envp);
            if(!expanded_value)
                return 0;
            file[i].value = expanded_value;
        }
        i++;
    }
    return 1;
}