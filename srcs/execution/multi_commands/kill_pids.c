/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kill_pids.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 17:15:47 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 17:24:50 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_pid(t_pid **list, int pid)
{
	t_pid	*new_pid = gc_malloc(sizeof(t_pid));
	t_pid	*tmp;

	new_pid->pid = pid;
	new_pid->next = NULL;
	if (!*list)
	{
		*list = new_pid;
		return;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_pid;
}

void	kill_pids(t_pid *list)
{
	while (list)
	{
		kill(list->pid, SIGKILL);
		waitpid(list->pid, NULL, 0);
		list = list->next;
	}
}

