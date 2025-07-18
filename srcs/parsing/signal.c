/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 22:50:53 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/18 22:41:42 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig_hander = 0;

void	handle_signal(int sig)
{
	if (sig == SIGINT)
	{
		if (waitpid(-1, NULL, WNOHANG) == 0)
			return ;
		if (g_sig_hander == HEREDOC_MODE)
		{
			ioctl(STDIN_FILENO, TIOCSTI, "\n");
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
		{
			write(STDOUT_FILENO, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			rl_redisplay();
		}
		g_sig_hander = CTRL_C;		
	}
}

void	init_signals(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);
}
