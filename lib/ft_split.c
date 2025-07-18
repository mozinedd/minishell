/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:22:41 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/18 21:04:49 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	count_word(char *s, char c)
{
	size_t	i;
	size_t	count;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c && s[i])
			i++;
		if (s[i])
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
	}
	return (count);
}

static size_t	len_words(char *s, char c)
{
	size_t	i;

	i = 0;
	while (*s && *s == c)
		s++;
	while (*s && *s != c)
	{
		s++;
		i++;
	}
	return (i);
}

static void	split_free(char **arr, size_t i)
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

static char	**alloc_words(char **arr, char *s, char c, size_t count)
{
	size_t	i;
	size_t	wlen;
	size_t	j;

	wlen = 0;
	i = 0;
	while (i < count)
	{
		wlen = len_words(s, c);
		arr[i] = (char *)malloc((wlen + 1) * sizeof(char));
		if (arr[i] == NULL)
		{
			split_free(arr, i);
			return (NULL);
		}
		j = 0;
		while (*s == c)
			s++;
		while (j < wlen)
			arr[i][j++] = *(s++);
		arr[i++][j] = '\0';
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char *s, char c)
{
	size_t	count_words;
	char	**arr;

	if (s == NULL)
		return (NULL);
	count_words = count_word(s, c);
	arr = gc_malloc((count_words + 1) * sizeof(char *));
	return (alloc_words(arr, s, c, count_words));
}
