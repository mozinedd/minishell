#include "minishell.h"

static size_t	count_word(char *s)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] && is_space(s[i]))
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && !is_space(s[i]))
				i++;
		}
	}
	return (count);
}

static size_t	len_words(char *s)
{
	size_t	i;

	i = 0;
	while (*s && is_space(*s))
		s++;
	while (s[i] && !is_space(s[i]))
		i++;
	return (i);
}

static void	free_sp(char **arr, size_t i)
{
	size_t	n;

	n = 0;
	while (n < i)
	{
		free(arr[n]);
		n++;
	}
	free(arr);
}

static char	**alloc_words(char **arr, char *s, size_t count)
{
	size_t	i;
	size_t	j;
	size_t	wlen;

	i = 0;
	while (i < count)
	{
		wlen = len_words(s);
		while (*s && is_space(*s))
			s++;
		arr[i] = (char *)malloc((wlen + 1) * sizeof(char));
		if (!arr[i])
			return (free_sp(arr, i), NULL);
		j = 0;
		while (j < wlen)
		{
			arr[i][j] = *(s++);
			j++;
		}
		arr[i][j] = '\0';
		i++;
	}
	return (arr[i] = NULL, arr);
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
