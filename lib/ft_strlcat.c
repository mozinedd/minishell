#include "minishell.h"

int	ft_strlcat(char *dst, char *src, int dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	while (src[i] && (len_dst + i) < (dstsize - 1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}