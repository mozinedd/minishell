
#include "../includes/minishell.h"

char	*ft_strdup(char *s1)
{
	int		len;
	char	*copys1;
	char	*src;

	len = ft_strlen(s1) + 1;
	src = (char *) s1;
	copys1 = (char *) malloc(len);
	if (copys1 == NULL)
		return (NULL);
	ft_memcpy(copys1, src, len);
	return (copys1);
}
