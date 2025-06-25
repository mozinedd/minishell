
#include "minishell.h"

t_file *init_files_of_commands(t_tokens *token)
{
	t_file *file;
	int count = 0;

	while (token && (token)->type != PIPE)
	{
		if (is_redirection(token))
			count++;
		token = (token)->next;
	}

	file  = malloc(sizeof(t_file) * (count + 1));
	if(!file)
		return NULL;
	return file;
}

int fill_files(t_file *files, t_tokens **token, t_environment *env)
{
	int i = 0;;
	t_tokens *tmp;
	
	tmp = *token;
	while (*token && (*token)->type != PIPE)
	{
		if (is_redirection(*token))
		{
			files[i].type = (*token)->type;
			if((*token)->next && (*token)->next->type == WORD)
			{
				files[i].value = ft_strdup((*token)->next->str);
				if(!files[i].value)
					return 0;
				i++;
				*token = (*token)->next;
			}
			else
				return 0;
		}
		*token = (*token)->next;
	}
	files[i].type = 0;
	files[i].value = NULL;
	*token = tmp;
	return expand_var(files, env);
}

t_commands *init_command_node()
{
	t_commands *command = malloc(sizeof(t_commands));
	if (!command)
		return NULL;
	command->cmd = NULL;
	command->file = NULL;
	command->next = NULL;
	return command;
}

t_commands *create_commands(t_tokens *token, t_environment *env)
{
	t_commands *head = NULL;
	t_commands *tmp = NULL;
	while (token)
	{
		t_commands *new_node = init_command_node();
		if (!new_node)
		{
			free_commands(head);
			return NULL;
		}
		new_node->file = init_files_of_commands(token);
		if (!new_node->file)
		{
			free_commands(head);
			return NULL;
		}
		if (!fill_files(new_node->file, &token, env))
		{
			free_commands(head);
			return NULL;
		}
		new_node->cmd = fill_command(join_commands(&token, env));
		if(!new_node->cmd)
		{
			free_commands(head);
			return NULL;      
		}
		if (!head)
			head = new_node;
		else
			tmp->next = new_node;
		tmp = new_node;
		if (token && token->type == PIPE)
			token = token->next;
	}
	return head;
}
t_commands *return_quts(t_commands **command)
{
	t_commands *current;
	int i;
	int j;

	current = *command;
	while(current)
	{
		i = 0;
		while (current->cmd[i])
		{
			j = 0;
			while(current->cmd[i][j] != '\0')
			{
				if(current->cmd[i][j] == 5)
					current->cmd[i][j] = '\'';
				else if (current->cmd[i][j] == 6)
					current->cmd[i][j] = '\"';
				j++;
			}
			i++;
		}
		i = 0;
		while (current->file[i].value)
		{
			j = 0;
			while(current->file[i].value[j])
			{
				if(current->file[i].value[j] == 5)
					current->file[i].value[j] = '\'';
				else if(current->file[i].value[j] == 6)
					current->file[i].value[j] = '\"';
				j++;
			}
			i++;
		}
		current = current->next;
	}
	 return *command;
}
int	has_quotes(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if(str[i] == '\'' || str[i] == '\"')
			return 1;
		i++;
	}
	return 0;
}
t_commands *final_commandes(t_commands **command)
{
	t_commands *current;
	int i;

	current = *command;
	while(current)
	{
		i = 0;
		while(current->cmd[i])
		{
			current->cmd[i] = remove_quts(current->cmd[i]);
			i++;
		}
		i = 0;
		while(current->file[i].value)
		{
			if(size_cmd(current->file[i].value) != 1)
				current->file[i].value = NULL;
			else
			{
				current->file[i].found_quts = has_quotes(current->file[i].value);
				current->file[i].value = remove_quts(current->file[i].value);	
			}
			i++;    
		}
		current = current->next;
	}
	return return_quts(command);
}



