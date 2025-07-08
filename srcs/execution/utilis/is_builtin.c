/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:02:58 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/08 16:03:17 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_builtin(t_cmds *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(cmd->cmd[0], "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd->cmd[0], "exit", 4) == 0)
		return (1);
	else
		return (0);
}

int	exec_is_builtin(t_env **env, t_cmds *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strncmp(*cmd->cmd, "echo", 4) == 0)
		return (ft_echo(cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "cd", 2) == 0)
		return (ft_cd(*env, cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "pwd", 3) == 0)
		return (ft_pwd(*env), 1);
	else if (ft_strncmp(*cmd->cmd, "export", 6) == 0)
		return (ft_export(env, cmd->cmd), 1);
	else if (ft_strncmp(*cmd->cmd, "unset", 5) == 0)
		return (ft_unset(cmd->cmd, env), 1);
	else if (ft_strncmp(*cmd->cmd, "env", 3) == 0)
		return (ft_env(*env), 1);
	else if (ft_strncmp(*cmd->cmd, "exit", 4) == 0)
		return (ft_exit(cmd->cmd), 1);
	else
		return (0);
}