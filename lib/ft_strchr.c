#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	size_t			i;
	unsigned char	ch;

	ch = (unsigned char) c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
		{
			return ((char *)&s[i]);
		}
		i++;
	}
	if (ch == '\0' && s[i] == '\0')
		return ((char *)&s[i]);
	return (NULL);
}
