
#include "../../includes/minishell.h"

// libere tous les tokens
void free_token(t_tokens *token)
{
	t_tokens *tmp;

	while(token)
	{
		tmp = token;
		token = token->next;
		free(tmp->str);
		free(tmp);
	}
}
