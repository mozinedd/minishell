/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:13:38 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 21:14:20 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	gc_free(void)
{
	t_gc	*current;
	t_gc	*next;

	current = *get_garbage_collector();
	while (current)
	{
		next = current->next;
		free(current->ptr);
		free(current);
		current = next;
	}
	*get_garbage_collector() = NULL;
}
