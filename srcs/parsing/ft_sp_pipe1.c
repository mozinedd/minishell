#include "minishell.h"

size_t count_pipes(char *line)
{
	int i;
	size_t count;

	if (!line)
		return (0);
	i = 0;
	count = 1;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			skip_to_next(line, &i);
			continue;
		}
		if (line[i] == '|')
			count++;
		i++;
	}
	return (count);
}

// void safe_free(char **arr, size_t idx)
// {
// 	size_t n;

// 	n = 0;
// 	while (n < idx)
// 	{
// 		free(arr[n]);
// 		n++;
// 	}
// 	free(arr);
// }

static int is_in_quotes_at_pos(char *str, int pos)
{
	int i;
	int in_single;
	int in_double;

	i = 0;
	in_single = 0;
	in_double = 0;
	while (i < pos)
	{
		if (str[i] == '\'' && !in_double)
			in_single = !in_single;
		else if (str[i] == '"' && !in_single)
			in_double = !in_double;
		i++;
	}
	return (in_single || in_double);
}

char	*trim_spaces(char *str)
{
	char	*start;
	char	*end;
	char	*res;
	size_t	len;

	if (!str || !*str)
		return (ft_strdup(""));
	start = str;
	while ((*start == ' ' || *start == '\t')
		&& !is_in_quotes_at_pos(str, start - str))
		start++;
	end = str + ft_strlen(str) - 1;
	while (end > start && (*end == ' ' || *end == '\t')
		&& !is_in_quotes_at_pos(str, end - str))
		end--;
	len = end - start + 1;
	res = gc_malloc(len + 1);
	ft_strlcpy(res, start, len + 1);
	// free(str);
	return (res);
}

