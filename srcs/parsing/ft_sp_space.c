#include "minishell.h"

static size_t	count_word(char *s)
{
	size_t	i = 0;
	size_t	count = 0;

	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !is_space(s[i]))
			{
				if (s[i] == '\'' || s[i] == '"')
					skip_to_next(s, (int *)&i);
				else
					i++;
			}
		}
	}
	return (count);
}

static size_t	len_words(char *s)
{
	size_t	i = 0;

	while (s[i] && !is_space(s[i]))
	{
		if (s[i] == '\'' || s[i] == '"')
			skip_to_next(s, (int *)&i);
		else
			i++;
	}
	return (i);
}

static void	free_sp(char **arr, size_t i)
{
	size_t	n = 0;

	while (n < i)
	{
		free(arr[n]);
		n++;
	}
	free(arr);
}

static char	**alloc_words(char **arr, char *s, size_t count)
{
	size_t	i = 0, j, wlen;

	while (i < count)
	{
		while (*s && is_space(*s))
			s++;
		wlen = len_words(s);
		arr[i] = malloc((wlen + 1) * sizeof(char));
		if (!arr[i])
			return (free_sp(arr, i), NULL);
		j = 0;
		while (j < wlen)
		{
			arr[i][j++] = *s++;
		}
		arr[i][j] = '\0';
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split_whitespace(char *s)
{
	size_t	count;
	char	**arr;

	if (!s)
		return (NULL);
	count = count_word(s);
	arr = gc_malloc((count + 1) * sizeof(char *));
	return (alloc_words(arr, s, count));
}