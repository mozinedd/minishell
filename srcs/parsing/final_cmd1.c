#include "minishell.h"

t_file	*init_files_of_commands(t_tokens *token)
{
	int		count;
	t_file	*file;

	count = 0;
	while (token && token->type != PIPE)
	{
		if (is_redirection(token))
			count++;
		token = token->next;
	}
	file = gc_malloc(sizeof(t_file) * (count + 1));
	return (file);
}

static int	process_redirection(t_file *files, int *i, t_glob *global)
{
	files[*i].type = global->token->type;
	if (global->token->next && global->token->next->type == WORD)
	{
		files[*i].value = ft_strdup(global->token->next->str);
		if (!files[*i].value)
			return (0);
		(*i)++;
		global->token = global->token->next;
	}
	else
		return (0);
	return (1);
}

int	fill_files(t_file *files, t_glob *global)
{
	int			i;
	t_tokens	*tmp;

	if (!files || !global || !global->token)
		return (0);
	i = 0;
	tmp = global->token;
	while (global->token && global->token->type != PIPE)
	{
		if (is_redirection(global->token))
		{
			if (!process_redirection(files, &i, global))
				return (0);
		}
		global->token = global->token->next;
	}
	files[i].type = 0;
	files[i].value = NULL;
	global->token = tmp;
	return (expand_var(files, global));
}

t_cmds	*init_command_node(void)
{
	t_cmds	*command;

	command = gc_malloc(sizeof(t_cmds));
	command->cmd = NULL;
	command->file = NULL;
	command->next = NULL;
	return (command);
}

// void	cleanup_and_free(t_cmds *head, t_cmds *new_node)
// {
// 	if (new_node)
// 	{
// 		if (new_node->file)
// 			free(new_node->file);
// 		free(new_node);
// 	}
// 	free_commands(head);
// }