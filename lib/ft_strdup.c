/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:39:38 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/09 16:52:15 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(char *s1)
{
	int		len;
	char	*copys1;
	char	*src;
	if (!s1)
		return NULL;
	len = ft_strlen(s1) + 1;
	src = (char *) s1;
	copys1 = (char *)malloc(len);
	if (!copys1)
		return (NULL);
	ft_memcpy(copys1, src, len);
	return (copys1);
}

