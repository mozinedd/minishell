#include "minishell.h"

int g_sig_hander;

void	handle_signal(int sig)
{
	if(sig == SIGINT)
	{
		if(g_sig_hander == 16)// = 16 pour juste separer que ici on travail sur herdoc
		{
			g_sig_hander = 1;
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
	}
}

void init_signals()
{
	rl_catch_signals = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, SIG_IGN);	
}