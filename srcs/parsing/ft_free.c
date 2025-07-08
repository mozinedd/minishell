
#include "minishell.h"

void	free_tokens(t_tokens *token)
{
	t_tokens	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_cmd_files(t_file *files)
{
	int	i;

	if (!files)
		return ;
	i = 0;
	while (files[i].value)
	{
		free(files[i].value);
		i++;
	}
	free(files);
}

void	free_commands(t_cmds *commands)
{
	t_cmds	*tmp;

	while (commands)
	{
		tmp = commands;
		commands = commands->next;
		if (tmp->cmd)
			free_arr(tmp->cmd);
		if (tmp->file)
			free_cmd_files(tmp->file);
		free(tmp);
	}
}

void	free_split(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

