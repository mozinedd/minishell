#include "minishell.h"

//creer un nouveau token

t_tokens *new_token(char *str, t_token_type type)
{
	t_tokens *token;

	token = malloc(sizeof(t_tokens));
	if(!token)
		return NULL;
	token->str = str;
	token->type = type;
	token->next = NULL;

	return token;
}

//ajouter un token a la fin de la liste

void add_token(t_tokens **token, t_tokens *new)
{
	t_tokens *tmp;

	if(!*token)
	{
		*token = new;
		return;
	}
	tmp = *token;
	while(tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}
int is_space(char c)
{
	return( c==  ' ' || c == '\t');///add more
}
void handl_op(char *str, int *i, t_tokens **token)
{
	if(ft_strncmp(&str[*i],">>", 2) == 0)
	{
		add_token(token, new_token(NULL, APPEND));
		(*i) = (*i) + 2;
	}
	else if(ft_strncmp(&str[*i], "<<", 2) == 0)
	{
		add_token(token, new_token(NULL, HERDOC));
		(*i) = (*i) + 2;		
	}
	else if(str[*i] == '>')
	{
		add_token(token, new_token(NULL, REDIR_OUT));
		(*i) = (*i) + 1;	
	}
	else if(str[*i] == '<')
	{
		add_token(token, new_token(NULL, REDIR_IN));
		(*i) = (*i) + 1;		
	}
	else if(str[*i] == '|')
	{
		add_token(token, new_token(NULL, PIPE));
		(*i) = (*i) + 1;		
	}
}

t_tokens *tokenize_cmd(char *line)
{
	t_tokens *token = NULL;
	int i;
	int start;

	i = 0;
	while(line[i])
	{
		if(is_space(line[i]))
		{
			i++;
			continue;
		}
		if(is_operator(line[i]))
			handl_op(line, &i, &token);
		else
		{
			start = i;
			while(1)
			{
				if(line[i] == '\'' || line[i] == '\"')
				{
					skip_to_next(line, &i);
					continue;
				}
				if(line[i] == '\0' || is_space(line[i]) || is_operator(line[i]))
					break;
				i++;
			}
			add_token(&token, new_token(ft_substr(line, start, i - start), WORD));
		}
	}
	return token;
}

