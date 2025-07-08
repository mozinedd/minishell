#include "minishell.h"

int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '"')
			return (1);
		i++;
	}
	return (0);
}

static void	remove_quotes_from_files(t_commands *cmd)
{
	int	i;

	i = 0;
	while (cmd->file[i].value)
	{
		if (size_cmd(cmd->file[i].value) != 1)
			cmd->file[i].value = NULL;
		else
		{
			cmd->file[i].found_quts = has_quotes(cmd->file[i].value);
			cmd->file[i].value = remove_quts(cmd->file[i].value);
		}
		i++;
	}
}

static void	remove_quotes_from_cmd(t_commands *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmd[i])
	{
		cmd->cmd[i] = remove_quts(cmd->cmd[i]);
		i++;
	}
}

t_commands	*final_commandes(t_commands **command)
{
	t_commands	*current;

	current = *command;
	while (current)
	{
		remove_quotes_from_cmd(current);
		remove_quotes_from_files(current);
		current = current->next;
	}
	return (return_quts(command));
}
