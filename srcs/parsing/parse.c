/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:46:54 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/18 21:25:16 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmds	*parsing(t_glob *global)
{
	char	*line;

	if (!global)
		return (NULL);
	line = read_command_line();
	if (!line)
		return (NULL);
	global->token = lexer(line, global);
	if (!global->token)
		return (NULL);
	if (!check_redirections(global->token))
	{
		exit_status(258, 0);
		return (NULL);
	}
	global->cmd = create_commands(global);
	global->cmd = final_commandes(&global->cmd);
	if (!global->cmd)
		return (NULL);
	return (global->cmd);
}

t_glob	*init_global_struct(void)
{
	t_glob	*global;

	global = gc_malloc(sizeof(t_glob));
	global->cmd = NULL;
	global->token = NULL;
	global->env = NULL;
	global->in_double_quotes = 0;
	global->exit_status = 0;
	get_terminal(&global->origin);
	return (global);
}

static void	init_env_if_null(t_env **env)
{
	char	**cmd;

	cmd = gc_malloc(sizeof(char *) * 6);
	cmd[0] = ft_strdup("export");
	cmd[1] = ft_strdup("PWD=/mnt/homes/mozinedd/Desktop/linux-verion-mini");
	cmd[2] = ft_strdup("SHLVL=1");
	cmd[3] = ft_strdup("_=/usr/bin/env");
	cmd[4] = ft_strdup("PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	cmd[5] = NULL;
	ft_export(env, cmd);
}

static void	run_loop(t_glob *global)
{
	while (1 && global)
	{
		dup2(2, 0);
		dup2(2, 1);
		set_terminal(&global->origin);
		global->cmd = parsing(global);
		if (open_heredoc(global))
		{
			close_heredoc(global);
			continue ;
		}
		if (global->cmd)
		{
			execute_command(global);
			close_heredoc(global);
		}
	}
}

int	mshll_loop(char **envp)
{
	t_glob	*global;
	t_env	*env;

	global = init_global_struct();
	if (!global)
		return (perror("msh: error allocating memory"), 0);
	env = list_of_env(envp);
	if (!env)
		init_env_if_null(&env);
	global->env = env;
	init_signals();
	run_loop(global);
	gc_free();
	return (1);
}
