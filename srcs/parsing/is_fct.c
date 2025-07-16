/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_fct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:31:32 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:31:33 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

int	is_quote(char c)
{
	return (c == '\'' || c == '\"');
}

int	is_redirection(t_tokens *type)
{
	return (type->type == APPEND || type->type == REDIR_IN
		|| type->type == REDIR_OUT || type->type == HERDOC);
}

int	is_operator(char c)
{
	return (c == '>' || c == '<' || c == '|');
}
