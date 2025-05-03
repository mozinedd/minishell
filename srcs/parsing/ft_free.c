/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/03 16:23:22 by ysouaf            #+#    #+#             */
/*   Updated: 2025/05/03 16:23:23 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

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
