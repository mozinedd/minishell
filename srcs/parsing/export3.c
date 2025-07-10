#include "minishell.h"

char	**do_job(char **sp)
{
	int		i;
	int		flag2;
	char	*str;

	i = 0;
	flag2 = 0;
	while (sp[i])
	{
		str = ft_strdup(sp[i]);
		if (!str)
			return (NULL);
		str = remove_quts(str);
		if (ft_strncmp(sp[i], str, -1) != 0)
			flag2 = 1;
		if (ft_strncmp(str, "export", 6) == 0)
			i = handle_export_command(sp, i, flag2);
		else
			i++;
	}
	return (sp);
}

char	*reconstruct_line(char **words)
{
	int		i;
	char	*line;
	char	*tmp;

	if (!words || !words[0])
		return (NULL);
	line = ft_strdup(words[0]);
	if (!line)
		return (NULL);
	i = 1;
	while (words[i])
	{
		tmp = ft_strjoin2(line, " ");
		// free(line);
		line = ft_strjoin2(tmp, words[i]);
		// free(tmp);
		if (!line)
			return (NULL);
		i++;
	}
	return (line);
}

static char	*process_single_line(char *line)
{
	char	**split_line;
	char	*new_line;

	split_line = ft_split_whitespace(line);
	if (!split_line)
		return (NULL);
	split_line = do_job(split_line);
	new_line = reconstruct_line(split_line);
	if (!new_line)
		return (NULL);
	return (new_line);
}

char	**operate_export(char **lines)
{
	int		i;
	char	*new_line;

	if (!lines)
		return (NULL);
	i = 0;
	while (lines[i])
	{
		new_line = process_single_line(lines[i]);
		if (!new_line)
		{
			i++;
			continue ;
		}
		// free(lines[i]);
		lines[i] = new_line;
		i++;
	}
	return (lines);
}
