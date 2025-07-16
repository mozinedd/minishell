/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:21:16 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 21:21:37 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest;
	const char		*srrc;

	i = 0;
	dest = (unsigned char *)dst;
	srrc = (const char *)src;
	if (dest == NULL && srrc == NULL)
		return (dest);
	while (i < n)
	{
		dest[i] = srrc[i];
		i++;
	}
	return (dest);
}
