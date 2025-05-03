#include "../includes/minishell.h"

char *ft_strndup(const char *s, size_t n)
{
	size_t i;
	size_t j;
	char *copy;

	i = 0;
	while (s[i] && i < n)
		i++;
	copy = (char *)malloc(i + 1);
	if (!copy)
		return (NULL);
	j = 0;
	while (j < i )
	{
		copy[j] = s[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
