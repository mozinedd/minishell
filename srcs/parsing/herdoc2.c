/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:31:14 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:31:22 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_heredoc_file(t_file *file, t_glob *global)
{
	int	fd;

	if (file->type == HERDOC)
	{
		fd = creat_herdoc(file->value, global, file->fd, file->found_quts);
		if (fd == -1)
			return (1);
		file->fd = fd;
	}
	else
		file->fd = -1;
	return (0);
}

int	open_heredoc(t_glob *global)
{
	t_cmds	*tmp;
	int		i;

	if (!global || !global->cmd)
		return (0);
	tmp = global->cmd;
	while (tmp)
	{
		if (tmp->file)
		{
			i = 0;
			while (tmp->file[i].value)
			{
				if (handle_heredoc_file(&tmp->file[i], global))
					return (1);
				i++;
			}
		}
		tmp = tmp->next;
	}
	return (0);
}

void	close_heredoc(t_glob *global)
{
	t_cmds	*tmp;
	int		i;

	if (!global || !global->cmd)
		return ;
	tmp = global->cmd;
	while (tmp)
	{
		if (!tmp->file)
		{
			tmp = tmp->next;
			continue ;
		}
		i = 0;
		while (tmp->file[i].value)
		{
			if (tmp->file[i].type == HERDOC && tmp->file[i].fd >= 0)
			{
				close(tmp->file[i].fd);
				tmp->file[i].fd = -2;
			}
			i++;
		}
		tmp = tmp->next;
	}
}
