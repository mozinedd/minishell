/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:59:41 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:00:49 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var_name(char *name)
{
	int	j;

	j = 0;
	while (name[j])
	{
		if (name[j] == '\'' || name[j] == '"' || name[j] == '$')
			return (1);
		j++;
	}
	return (0);
}

static char	*add_quotes_to_value(char *value)
{
	char	*tmp;
	char	*quoted;

	tmp = ft_strjoin2("\"", value);
	if (!tmp)
		return (NULL);
	quoted = ft_strjoin2(tmp, "\"");
	free(tmp);
	return (quoted);
}

static char	**process_equal_split(char **equal_split, int flag, int flag2)
{
	char	*original;
	char	*quoted;

	original = equal_split[0];
	equal_split[0] = ft_strjoin2(original, "=");
	free(original);
	if (flag == 0 && flag2 == 0 && !has_quotes(equal_split[1])
		&& !ft_isdigit(equal_split[0][0]))
	{
		quoted = add_quotes_to_value(equal_split[1]);
		free(equal_split[1]);
		equal_split[1] = quoted;
	}
	return (equal_split);
}

static char	**split_first_equal(char *str)
{
	char	**result;
	int		i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (!str[i])
		return (NULL);
	result = gc_malloc(sizeof(char *) * 3);
	result[0] = ft_substr(str, 0, i);
	result[1] = ft_strdup(str + i + 1);
	result[2] = NULL;
	return (result);
}

int	process_export_arg(char **sp, int i, int flag2)
{
	char	**equal_split;
	int		flag;
	char	*new_str;

	if (!there_is(sp[i], '='))
		return (i + 1);
	equal_split = split_first_equal(sp[i]);
	equal_split = trim_split_result(equal_split);
	if (!equal_split || !equal_split[0] || !equal_split[1])
		return (i + 1);
	flag = check_var_name(equal_split[0]);
	equal_split = process_equal_split(equal_split, flag, flag2);
	new_str = ft_strjoin2(equal_split[0], equal_split[1]);
	free(sp[i]);
	sp[i] = new_str;
	return (i + 1);
}
