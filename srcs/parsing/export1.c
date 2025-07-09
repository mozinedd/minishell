#include "minishell.h"

char	**trim_split_result(char **arr)
{
	int		i;
	char	*trimmed;

	i = 0;
	if (!arr)
		return (NULL);
	while (arr[i])
	{
		trimmed = ft_strtrim(arr[i], " \t\n\r\v\f");
		if (!trimmed)
			return (NULL);
		free(arr[i]);
		arr[i] = trimmed;
		i++;
	}
	return (arr);
}

int	red(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (1);
	if (ft_strncmp(str, ">", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 0)
		return (1);
	if (ft_strncmp(str, "<", 2) == 0)
		return (1);
	return (0);
}

int	there_is(char *str, char c)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}
