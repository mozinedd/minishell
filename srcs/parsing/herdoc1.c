/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   herdoc1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:29:59 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:30:04 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dollar(char *word)
{
	int	i;

	i = 0;
	while (word[i])
	{
		if (word[i] == '$' && !ft_isalnum(word[i + 1])
			&& word[i + 1] != '_' && word[i + 1] != '?')
			return (0);
		i++;
	}
	return (1);
}

void	write_herdoc_line(char *line, int fd_write, int flag, t_glob *global)
{
	char	*expanded;
	int		len;

	len = (int)ft_strlen(line);
	if (flag == 0)
	{
		expanded = herdoc_expand(line, 0, &len, global);
		write(fd_write, expanded, ft_strlen(expanded));
		free(expanded);
	}
	else
		write(fd_write, line, ft_strlen(line));
	write(fd_write, "\n", 1);
}

char	*generate_herdoc_name(void)
{
	static int	counter;
	char		*filename;
	char		*counter_str;

	while (1)
	{
		counter_str = ft_itoa(counter);
		if (!counter_str)
			return (NULL);
		filename = ft_strjoin2("/tmp/herdoc", counter_str);
		if (!filename)
			return (NULL);
		if (access(filename, F_OK) != 0)
			return (filename);
		counter++;
	}
	return (NULL);
}

int	open_herdoc_fds(char **filename, int *fd_read, int *fd_write)
{
	*filename = generate_herdoc_name();
	if (!*filename)
		return (-1);
	*fd_write = open(*filename, O_CREAT | O_WRONLY, 0644);
	*fd_read = open(*filename, O_RDONLY);
	unlink(*filename);
	if (*fd_write == -1 || *fd_read == -1)
		return (perror("heredoc"), -1);
	return (0);
}

int	creat_herdoc(char *delimiter, t_glob *global, int fd_read, int flag)
{
	int		fd_write;
	char	*line;
	char	*filename;

	g_sig_hander = HEREDOC_MODE;
	init_signals();
	if (open_herdoc_fds(&filename, &fd_read, &fd_write) == -1)
		return (-1);
	while (1)
	{
		line = readline("> ");
		if (g_sig_hander == CTRL_C)
			return (free(line), close(fd_write), -1);
		if (!line || ft_strncmp(delimiter, line, -1) == 0)
			break ;
		write_herdoc_line(line, fd_write, flag, global);
	}
	free(line);
	close(fd_write);
	return (fd_read);
}
