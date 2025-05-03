#ifndef MINISHELL_H
#define MINISHELL_H


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


typedef struct s_commands {
    char **cmd;         // Array of command and arguments
    char **inoutfile;   // Array of input/output files
    int fr_herdoc;      // File descriptor for heredoc
    struct s_commands *next;
    struct s_commands *prev;
} t_commands;



typedef enum e_token_type {
    WORD,       // string 
    HERDOC,     // <<
    APPEND,     // >>
    REDIR_IN,   // <
    REDIR_OUT,  // >
    PIPE,       // |
    ENV_VAR     // $variable
} t_token_type;

typedef struct s_tokens{
    char *str;
    t_token_type type;
    struct s_tokens *next;
}   t_tokens;


//command line functions
char *read_command_line();


//tokenization functions
t_tokens *new_token(char *str, t_token_type type);
void add_token(t_tokens **token, t_tokens *new);
t_tokens *tokenize_cmd(char *line);
void free_token(t_tokens *token);
int is_operator(char c);
void skip_to_next(char *str, int *i);
bool	syntax_error(t_tokens **token);
char	*ft_substr(char const *s, unsigned int start, size_t len);




// exec

typedef struct s_environment {
	char *key;
	char *value;
	struct s_environment *next;
} t_environment;


char			*ft_strchr(const char *s, int c);
char			*ft_strndup(const char *s, size_t n);
char	*ft_strdup(char *s1);
t_environment	*ft_lstnew(void *content);
t_environment 	*list_of_env(char **env);
t_environment 	*creat_node(char *env);
int 			ft_strlen(char *str);
void    *ft_memcpy(void *dst, const void* src, size_t n);

#endif
