/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 20:04:34 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/16 21:13:21 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*pointer;

	pointer = gc_malloc(count * size);
	if (!pointer)
		return (NULL);
	ft_memset(pointer, 0, count * size);
	return (pointer);
}
