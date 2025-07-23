/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozinedd <mozinedd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/17 19:02:58 by mozinedd          #+#    #+#             */
/*   Updated: 2025/07/23 16:34:19 by mozinedd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_is_builtin(t_cmds *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(cmd->cmd[0], "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "export") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "env") == 0)
		return (1);
	else if (ft_strcmp(cmd->cmd[0], "exit") == 0)
		return (1);
	return (0);
}

int	exec_is_builtin(t_env **env, t_cmds *cmd)
{
	if (!cmd)
		return (0);
	if (ft_strcmp(*cmd->cmd, "echo") == 0)
		return (ft_echo(cmd->cmd), 1);
	else if (ft_strcmp(*cmd->cmd, "cd") == 0)
		return (ft_cd(*env, cmd->cmd), 1);
	else if (ft_strcmp(*cmd->cmd, "pwd") == 0)
		return (ft_pwd(*env), 1);
	else if (ft_strcmp(*cmd->cmd, "export") == 0)
		return (ft_export(env, cmd->cmd), 1);
	else if (ft_strcmp(*cmd->cmd, "unset") == 0)
		return (ft_unset(cmd->cmd, env), 1);
	else if (ft_strcmp(*cmd->cmd, "env") == 0)
		return (ft_env(*env), 1);
	else if (ft_strcmp(*cmd->cmd, "exit") == 0)
		return (ft_exit(cmd->cmd), 1);
	else
		return (0);
}
