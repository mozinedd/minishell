#include "minishell.h"

static int	process_command_node(t_cmds *new_node, t_glob *global)
{
	char	*joined;

	new_node->file = init_files_of_commands(global->token);
	if (!new_node->file)
		return (0);
	if (!fill_files(new_node->file, global))
		return (0);
	joined = join_commands(global);
	if (!joined)
	{
		new_node->cmd = malloc(sizeof(char *));
		if (!new_node->cmd)
			return (0);
		new_node->cmd[0] = NULL;
		return (1);
	}
	new_node->cmd = fill_command(joined);
	free(joined);
	if (!new_node->cmd)
		return (0);
	return (1);
}

t_cmds	*create_commands(t_glob *global)
{
	t_cmds	*head;
	t_cmds	*tmp;
	t_cmds	*new_node;

	if (!global)
		return (NULL);
	head = NULL;
	tmp = NULL;
	while (global->token)
	{
		new_node = init_command_node();
		if (!new_node)
			return (free_commands(head), NULL);
		if (!process_command_node(new_node, global))
			return (cleanup_and_free(head, new_node), NULL);
		if (!head)
			head = new_node;
		else
			tmp->next = new_node;
		tmp = new_node;
		if (global->token && global->token->type == PIPE)
			global->token = global->token->next;
	}
	return (head);
}

static void	restore_quotes_in_cmd(t_cmds *cmd)
{
	int	i;
	int	j;

	i = 0;
	while (cmd->cmd[i])
	{
		j = 0;
		while (cmd->cmd[i][j])
		{
			if (cmd->cmd[i][j] == 5)
				cmd->cmd[i][j] = '\'';
			else if (cmd->cmd[i][j] == 6)
				cmd->cmd[i][j] = '"';
			j++;
		}
		i++;
	}
}

static void	restore_quotes_in_files(t_file *file)
{
	int	i;
	int	j;

	i = 0;
	while (file[i].value)
	{
		j = 0;
		while (file[i].value[j])
		{
			if (file[i].value[j] == 5)
				file[i].value[j] = '\'';
			else if (file[i].value[j] == 6)
				file[i].value[j] = '"';
			j++;
		}
		i++;
	}
}

t_cmds	*return_quts(t_cmds **command)
{
	t_cmds	*current;

	current = *command;
	while (current)
	{
		restore_quotes_in_cmd(current);
		restore_quotes_in_files(current->file);
		current = current->next;
	}
	return (*command);
}
