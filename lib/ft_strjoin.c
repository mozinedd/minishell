/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/02 22:48:14 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/16 21:46:58 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		len;
	char	*allstr;

	i = 0;
	j = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	allstr = gc_malloc(len + 1);
	if (!allstr)
		return (NULL);
	while (s1 != NULL && s1[i])
		allstr[j++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i])
		allstr[j++] = s2[i++];
	allstr[j] = '\0';
	return (allstr);
}
