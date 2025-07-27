/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:19:56 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/27 21:43:32 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_gc	**get_garbage_collector(void)
{
	static t_gc	*collector;

	return (&collector);
}

void	*gc_malloc(size_t size)
{
	void	*allocated_ptr;
	t_gc	*new_node;

	if (size == 0)
		return (NULL);
	allocated_ptr = malloc(size);
	if (!allocated_ptr)
		return (gc_free(), exit_status(1, 0), exit(1), NULL);
	ft_memset(allocated_ptr, 0, size);
	new_node = malloc(sizeof(t_gc));
	if (!new_node)
		return (gc_free(), exit_status(1, 0), exit(1), NULL);
	ft_memset(new_node, 0, sizeof(t_gc));
	new_node->ptr = allocated_ptr;
	new_node->next = *get_garbage_collector();
	*get_garbage_collector() = new_node;
	return (allocated_ptr);
}
