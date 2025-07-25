/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:44:25 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/16 22:44:26 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*remove_quts(char *line)
{
	int		i;
	int		st;
	char	*temp;
	char	*new_cmd;
	char	c[2];

	i = 0;
	new_cmd = ft_strdup("");
	c[1] = '\0';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			st = i + 1;
			skip_to_next(line, &i);
			temp = ft_substr(line, st, i - st - 1);
			new_cmd = ft_strjoin2(new_cmd, temp);
			continue ;
		}
		c[0] = line[i];
		new_cmd = ft_strjoin2(new_cmd, c);
		i++;
	}
	return (new_cmd);
}
