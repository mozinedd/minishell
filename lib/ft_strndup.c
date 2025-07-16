/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:51:29 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 21:51:35 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	size_t	j;
	char	*copy;

	i = 0;
	while (s[i] && i < n)
		i++;
	copy = gc_malloc(i + 1);
	if (!copy)
		return (NULL);
	j = 0;
	while (j < i)
	{
		copy[j] = s[j];
		j++;
	}
	copy[j] = '\0';
	return (copy);
}
