/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:18:36 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 21:19:14 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lstnew(void *content)
{
	t_env	*lst;

	lst = gc_malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->value = content;
	lst->next = NULL;
	return (lst);
}
