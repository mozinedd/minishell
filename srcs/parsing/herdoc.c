
#include "minishell.h"

int g_sig_hander;

void	write_herdoc_line(char *line, int fd_write, int flag, t_environment *env)
{
	char *expended;
	int len;

	len = (int)ft_strlen(line);
	expended = expand_from_to(line, 0, &len, env);
	if(flag == 0)
	{
		write(fd_write, expended, ft_strlen(expended));
		free(expended);
	}
	else
		write(fd_write, line, ft_strlen(line));
	write(fd_write, "\n", 1);
}
char *generate_herdoc_name() 
{
    static int counter = 0;
    char *base = "/tmp/herdoc";
    char *filename;
	char *counter_str;
	
    while (1)
	{
    	counter_str = ft_itoa(counter);
        if (!counter_str)
            return NULL;
        filename = ft_strjoin(base, counter_str);
        if (!filename)
            return NULL;
        if (access(filename, F_OK) != 0) {
            return filename;
        }
        counter++;
    }
	free(counter_str);
}
int creat_herdoc(char *delimiter, t_environment *env, int fd_read, int flag)
{
	int fd_write;
	char *line;
	char *filename;

	g_sig_hander = 16;	
	init_signals();
	filename = generate_herdoc_name();
	fd_write = open(filename, O_CREAT | O_WRONLY, 0644);
	fd_read = open(filename, O_RDONLY);
	unlink(filename);
	free(filename);
	if (fd_write == -1)
		return perror("heredoc"),-1;
	while(1)
	{
		line = readline("> ");
		if (g_sig_hander == 1)
		{
			free(line);
			return -1;
		}
		if (ft_strncmp(delimiter, line, -1) == 0 || !line)
        {
            if(line) free(line);
            break;
        }
		write_herdoc_line(line, fd_write, flag, env);
	}
	close(fd_write);
	return fd_read;	
}

void	search_herdoc(t_commands **command, t_environment *env)
{
	t_commands	*tmp;
	int	i;

	tmp = *command;
	while(tmp)
	{
		i = 0;
		while(tmp->file[i].value)
		{
			if(tmp->file[i].type == HERDOC)
			{
				tmp->file[i].fd = creat_herdoc(tmp->file[i].value, env, tmp->file[i].fd, tmp->file[i].found_quts);
				if (tmp->file[i].fd == -1)
					return ;
			}
			else
				tmp->file[i].fd = -1;
			i++;
		}
		tmp = tmp->next;
	}
	print_herdoc(command, env);
}
