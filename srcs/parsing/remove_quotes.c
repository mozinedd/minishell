#include "minishell.h"

char *remove_quts(char *line)
{
	int i = 0;
	int st;
	char *temp;
	char *new_cmd = ft_strdup("");
	char c[2];
	c[1] = '\0';
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			st = i + 1;
			skip_to_next(line, &i);
			temp = ft_substr(line, st, i - st - 1);
			new_cmd = ft_strjoin(new_cmd ,temp);
			continue;
		}
		c[0] = line[i];
		new_cmd = ft_strjoin(new_cmd ,c);
		i++;
	}
    free(line);
	return new_cmd;
}