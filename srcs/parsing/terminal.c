/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:02:01 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/24 16:02:06 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_terminal(struct termios *termios)
{
	if (tcgetattr(STDIN_FILENO, termios) == -1)
	{
		perror("tcgetattr");
	}
}

void	set_terminal(struct termios *termios)
{
	if (tcsetattr(STDIN_FILENO, TCSANOW, termios) == -1)
	{
		perror("tcsetattr");
	}
}
