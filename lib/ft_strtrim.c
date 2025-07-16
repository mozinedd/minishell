/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:52:10 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 21:52:11 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strrchr(char *s, int c)
{
	int		i;
	char	*sp;

	sp = (char *)s;
	i = ft_strlen(sp);
	while (i >= 0)
	{
		if (sp[i] == (char)c)
			return ((char *)(sp + i));
		i--;
	}
	return (NULL);
}

char	*ft_strtrim(char *s1, char *set)
{
	char	*start;
	char	*end;
	size_t	len;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	start = s1;
	end = s1 + ft_strlen(s1);
	while (*start && ft_strchr(set, (int)*start))
		start++;
	while (end > start && ft_strrchr(set, *(end - 1)))
		end--;
	len = end - start;
	return (ft_substr(start, 0, len));
}
