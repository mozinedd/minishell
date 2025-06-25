
#include "minishell.h"

// libère tous les tokens
void	free_token(t_tokens *token)
{
	t_tokens	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}
//free les commandes
void	free_commands(t_commands *commands)
{
	t_commands	*tmp;
	char		**cmd;
	t_file		*file;

	while (commands)
	{
		tmp = commands;
		commands = commands->next;
		if (tmp->cmd)
		{
			cmd = tmp->cmd;
			while (*cmd)
			{
				free(*cmd);
				cmd++;
			}
			free(tmp->cmd);
		}
		if (tmp->file)
		{
			file = tmp->file;
			while (file->type != 0)
			{
				free(file->value);
				file++;
			}
			free(tmp->file);
		}
		free(tmp);
	}
}

