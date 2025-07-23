/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/21 17:55:43 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 16:33:45 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_size(t_env *head)
{
	int		size;
	t_env	*tmp;

	size = 0;
	tmp = head;
	while (tmp)
	{
		size++;
		tmp = tmp->next;
	}
	return (size);
}

char	**env_to_array(t_env *head)
{
	int		i;
	int		size;
	char	**array;
	t_env	*tmp;
	char	*curent;

	(1) && (tmp = head, curent = NULL);
	size = env_size(head);
	array = gc_malloc(sizeof(char *) * (size +1));
	i = 0;
	while (i < size)
	{
		curent = ft_strjoin2(curent, tmp->key);
		if (tmp->value)
		{
			curent = ft_strjoin2(curent, "=");
			curent = ft_strjoin2(curent, tmp->value);
		}
		array[i] = curent;
		curent = NULL;
		tmp = tmp->next;
		i++;
	}
	array[size] = NULL;
	return (array);
}

char	*check_command_is_exist(t_env *env, char *cmd)
{
	char		*my_final_cmd;
	struct stat	mozinedd;

	if (!cmd)
		return (NULL);
	my_final_cmd = get_command_path(env, cmd);
	stat(my_final_cmd, &mozinedd);
	if (my_final_cmd == NULL)
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0
			&& S_ISDIR(mozinedd.st_mode) != 0)
			return (cmd);
		else
		{
			if (ft_getenv(env, "PATH") == NULL)
				return (ft_printf("mini: %s: No such file or direcotry\n", cmd)
					, exit (127), NULL);
			return (ft_printf("mini: %s: Command not found\n", cmd)
				, exit (127), NULL);
		}
	}
	if (S_ISDIR(mozinedd.st_mode) != 0)
		return (ft_printf("mini: %s: Is a directory\n", cmd), exit(126), NULL);
	return (my_final_cmd);
}

// char	*get_path(char **dirs, char *cmd)
// {
// 	char	*all_path;
// 	int		i;

// 	i = 0 ;
// 	while (dirs[i])
// 	{
// 		size_t len_dirs = ft_strlen(dirs[i]);
// 		size_t len_cmd = ft_strlen(cmd);
// 		size_t total_len = len_dirs + 1 + len_cmd + 1;
// 		all_path = gc_malloc(total_len);
// 		if (!all_path)
// 		{
// 			i++;
// 			continue;
// 		}
// 		ft_strcpy(all_path, dirs[i]);
// 		all_path[len_dirs] = '/';
// 		ft_strcpy(all_path + len_dirs + 1, cmd);
// 		if (access(all_path, F_OK) == 0)
// 			return all_path;
// 		i++;
// 	}
// 	return NULL;
// }

char	*get_path(char **dirs, char *cmd)
{
	char	*all_path;
	int		i;
	size_t	len_dirs;
	size_t	len_cmd;
	size_t	total_len;

	i = -1;
	while (dirs[++i])
	{
		len_dirs = ft_strlen(dirs[i]);
		len_cmd = ft_strlen(cmd);
		total_len = len_dirs + 1 + len_cmd + 1;
		all_path = gc_malloc(total_len);
		if (!all_path)
			continue ;
		ft_strcpy(all_path, dirs[i]);
		all_path[len_dirs] = '/';
		ft_strcpy(all_path + len_dirs + 1, cmd);
		if (access(all_path, F_OK) == 0)
			return (all_path);
	}
	return (NULL);
}

char	*get_command_path(t_env *env, char *cmd)
{
	char	*path_env;
	char	**dirs;
	char	*my_command;

	if (!env || !cmd || !ft_strcmp(cmd, ""))
		return (NULL);
	if (strchr(cmd, '/'))
		return (ft_strdup(cmd));
	path_env = ft_getenv(env, "PATH");
	if (!path_env)
		return (cmd);
	dirs = ft_split(path_env, ':');
	if (!dirs)
		return (NULL);
	my_command = get_path(dirs, cmd);
	return (my_command);
}
