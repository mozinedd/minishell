/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 20:07:55 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 20:07:58 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_env_value(char *varname, t_env *envp)
{
	t_env	*tmp;

	if (!varname || !envp)
		return (NULL);
	tmp = envp;
	while (tmp)
	{
		if (tmp->key && ft_strncmp(tmp->key, varname,
				ft_strlen(varname)) == 0
			&& ft_strlen(tmp->key) == ft_strlen(varname))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

char	*allocate_name_var(char *wrd, int *i)
{
	int		start;
	char	*varname;

	if (!wrd || !i)
		return (NULL);
	start = *i;
	if (ft_isdigit(wrd[*i]) || wrd[*i] == '$')
	{
		(*i)++;
		return (ft_strdup(" "));
	}
	while (ft_isalnum(wrd[*i]) || wrd[*i] == '_')
		(*i)++;
	varname = ft_substr(wrd, start, (*i) - start);
	return (varname);
}

char	*replace_word(char *word, int start, int end, char *replace)
{
	char	*new;
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	k = 0;
	if (!word || start < 0 || end < start || end > (int)ft_strlen(word))
		return (word);
	if (!replace)
		replace = "";
	new = gc_malloc(ft_strlen(word) - (end - start) + ft_strlen(replace) + 1);
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

char	*replace_quts(char *val)
{
	char	*new_val;
	int		i;

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
