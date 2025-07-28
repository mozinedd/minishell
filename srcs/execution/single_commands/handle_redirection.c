/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirection.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 16:07:42 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/28 17:41:26 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_append(int *outfile, t_file *tmp, int i)
{
	if (tmp[i].value == NULL || size_cmd(tmp[i].value) != 1)
		return (ft_printf("msh : ambiguous redirect\n"), -1);
	if (*outfile != -1)
		close(*outfile);
	*outfile = open (tmp[i].value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (*outfile == -1)
		return (-1);
	return (1);
}

int	redirection_redir_out(int *outfile, t_file *tmp, int i)
{
	if (!tmp[i].value || size_cmd(tmp[i].value) != 1)
		return (ft_printf("msh : ambiguous redirect\n"), -1);
	if (*outfile != -1)
		close(*outfile);
	*outfile = open (tmp[i].value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (*outfile == -1)
		return (-1);
	return (1);
}

int	redirection_redir_in(int *infile, t_file *tmp, int i)
{
	if (tmp[i].value == NULL || size_cmd(tmp[i].value) != 1)
		return (ft_printf("msh : ambiguous redirect\n"), -1);
	if (*infile != -1 && tmp[i].fd == -1)
		close(*infile);
	*infile = open (tmp[i].value, O_RDONLY);
	if (*infile == -1)
		return (-1);
	return (1);
}

int	all_redirection_checker(int i, int *outfile, int *infile, t_file *tmp)
{
	if (tmp[i].type == REDIR_OUT)
	{
		if (redirection_redir_out(outfile, tmp, i) == -1)
			return (-1);
	}
	else if (tmp[i].type == APPEND)
	{
		if (redirection_append(outfile, tmp, i) == -1)
			return (-1);
	}
	else if (tmp[i].type == HERDOC)
		*infile = tmp[i].fd;
	else if (tmp[i].type == REDIR_IN)
	{
		if (redirection_redir_in(infile, tmp, i) == -1)
			return (-1);
	}
	return (1);
}

int	redirection_handel(t_file *tmp)
{
	int	outfile;
	int	infile;
	int	i;

	infile = -2;
	outfile = -2;
	i = -1;
	while (tmp && tmp[++i].type)
	{
		if (all_redirection_checker(i, &outfile, &infile, tmp) == -1)
			return (-1);
	}
	if (infile > 0)
	{
		if (dup2(infile, 0) == -1)
			return (perror(""), -1);
		close(infile);
	}
	if (outfile > 0)
	{
		if (dup2(outfile, 1) == -1)
			return (perror(""), -1);
		close(outfile);
	}
	return (1);
}
