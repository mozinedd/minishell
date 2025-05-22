#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>
int is_space(char c)
{
	return( c==  ' ' || c == '\t');///add more
}
size_t ft_strlen(const char *s1)
{
    size_t i = 0;
    while(s1[i])
        i++;
    return i;

}
void    *ft_memcpy(void *dst, const void* src, size_t n)
{
    size_t i;
    unsigned char *dest;
    const char *srrc;
    
    i = 0;
    dest = (unsigned char *) dst;
    srrc = (const char *) src;
    if (dest == (NULL) && srrc == (NULL))
    return (dest);
    while (i < n)
    {
        dest[i] = srrc[i];
        i++;
    }
    return (dest);
    
}
char	*ft_strdup(char *s1)
{
	int		len;
	char	*copys1;
	char	*src;

	len = ft_strlen(s1) + 1;
	src = (char *) s1;
	copys1 = (char *) malloc(len);
	if (copys1 == NULL)
		return (NULL);
	ft_memcpy(copys1, src, len);
	return (copys1);
}
void skip_to_next(char *str, int *i)
{
	char quote;
	quote = str[*i];
	(*i)++;
	while(str[*i] != quote && str[*i] != '\0')
		(*i)++;
	if(str[*i])
		(*i)++;
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0 && (!s1 || !s2))
		return (0);
	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& s1[i] && s2[i] && i < n - 1)
		i++;
	if (n > 0)
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
	else
		return (0);
}
int size_cmd(char *expanded_word)
{
	int i;
	int count = 0;

	i = 0;
	while(expanded_word[i])
	{
		if(is_space(expanded_word[i]))
		{
			i++;
			continue;
		}
		else
		{
			while(1)
			{
				if(expanded_word[i] == '\'' || expanded_word[i] == '\"')
				{
					skip_to_next(expanded_word, &i);
					continue;
				}
				if(expanded_word[i] == '\0' || is_space(expanded_word[i]))
					break;
				
				i++;
			}
            count++;
		}
	}
	return count;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*substr;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
		return (ft_strdup(""));
	if (len > s_len - start)
		len = s_len - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}
char **fill_command(char *joined_str)
{
    int i;
	int j = 0;
    char **cmd;
    int start;

    cmd = malloc(sizeof(char *) * (size_cmd(joined_str) + 1));
    if(!cmd)
        return NULL;
    
	i = 0;
	while(joined_str[i])
	{
		if(is_space(joined_str[i]))
		{
			i++;
			continue;
		}
		else
		{
            start = i;
			while(1)
			{
				if(joined_str[i] == '\'' || joined_str[i] == '\"')
				{
					skip_to_next(joined_str, &i);
					continue;
				}
				if(joined_str[i] == '\0' || is_space(joined_str[i]))
					break;
				
				i++;
			}
            cmd[j] = ft_substr(joined_str, start, i - start);
            j++;
		}
	}
    cmd[j] = NULL;
	return cmd;
}
size_t	ft_strlcat(char *dst, char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	if (dst == NULL && dstsize == 0)
		return (ft_strlen(src));
	i = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	while (src[i] && (len_dst + i) < (dstsize - 1))
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
size_t	ft_strlcpy(char *dst,char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
		dst[i] = '\0';
	return (ft_strlen(src));
}

char	*ft_strjoin(char  *s1, char  *s2)
{
	char	*s3;
	size_t	len;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else if (!s2)
		return (ft_strdup(s1));
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s3 = malloc(sizeof(char) * len);
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, len);
	ft_strlcat(s3, s2, len);
	return (s3);
}
char *remove_quts(char *line)
{
	int i = 0;
	int st;
	int end;
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
	return new_cmd;
}
int is_operator(char c)
{
    return (c == '>' || c == '<' || c == '|');
}
int no_op_in_line(char *line)
{
	int i = 0;
	while(line[i])
	{
		if(line[i] == '>' || line[i] == '<' | line[i] == '|')
			return 0;
		i++;
	}
	return 1;
}
char *read_command_line()
{
    char *line;

    line = readline("minishell$ ");

    if(!line)
    {
        return NULL;
    }
	if(!no_op_in_line(line))
	{
		while(*line && is_space(*line))
			line++;
		if(ft_strncmp(line, "minishell", 10))
			return line;
	}
    add_history(line);
    return line;
}

int main(int c, char **av)
{
    // char str[51] = "yassine souaf cv bikhir hani         .     ?      ";
    // char **cmd = fill_command(str);
    // int32_t j= 0;
    // while(cmd[j])
    // {
    //     printf("cmd --> %s \n", cmd[j]);
	// 	printf("\n sans quotes ---> %s \n", remove_quts(cmd[j]));
    //     j++;
    // }
	printf ("ar :%s.\n",av[1]);
	printf ("n  :%s.\n",remove_quts(av[1]));
}