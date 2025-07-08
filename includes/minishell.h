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


typedef enum e_token_type {
    WORD,       // string 
    HERDOC,     // <<
    APPEND,     // >>
    REDIR_IN,   // <
    REDIR_OUT,  // >
    PIPE,       // |
} t_token_type;

typedef struct s_file
{
    t_token_type type;
    char *value;
} t_file;

// typedef struct s_commands {
//     char **cmd;        
//     t_file *file;
//     struct s_commands *next;
// } t_commands;
typedef struct s_cmds {
    char **cmd;
    char **inoutfile;
	int heredoc_fd;
    struct s_cmds *next ;
    struct s_cmds *prev;
} t_cmds;

typedef struct s_tokens{
    char *str;
    t_token_type type;
    struct s_tokens *next;
}   t_tokens;

/*================parsing================*/
//command line functions
char *read_command_line();


//tokenization functions
t_tokens *new_token(char *str, t_token_type type);
void add_token(t_tokens **token, t_tokens *new);
t_tokens *tokenize_cmd(char *line);
int is_operator(char c);
void skip_to_next(char *str, int *i);
bool	syntax_error(t_tokens **token);
int is_redirection(t_tokens *type);

//lib
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);


//free
void free_token(t_tokens *token);
void free_commands(t_cmds *commands);


//commandes
t_cmds *create_commands(t_tokens *token);



/*==========execution=============*/

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
} t_env;


char			*ft_strchr(const char *s, int c);
char			*ft_strndup(const char *s, size_t n);
char	*ft_strdup(char *s1);
void	ft_env(t_env *env);
size_t			ft_strlen(const char *str);
void    *ft_memcpy(void *dst, const void* src, size_t n);
void    ft_putchar(char c);
int	ft_isdigit(int c);
int	ft_atoi(const char *str);
void handle_single_command (t_cmds *cmd, t_env *env);
char **ft_split(char const *s, char c);
char	*ft_strcpy(char *dest, char *src);
t_env *list_of_env(char **env);

void	*ft_memset(void *b, int c, size_t len);
void	*ft_calloc(size_t count, size_t size);
int		ft_cd(t_env *env, char **args);
int		ft_echo(char **args);
int		ft_exit(char **args);
void	ft_pwd(t_env *env);
int	ft_strcmp(const char *s1, const char *s2);
int	check_is_builtin(t_cmds *cmd);
int	exec_is_builtin(t_env **env, t_cmds *cmd);
char **env_to_array(t_env *head);
char	*get_command_path(t_env *env, char *cmd);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
void	ft_export (t_env **env, char **cmd);
int exit_status(int status, int is_get);
int ft_unset(char **args, t_env **env);
char    *ft_strjoin(char const *s1, char const *s2);
int		detect_overflow(int is_set, int my_status);
// todo : come back here
char *ft_getenv(t_env *env, const char *key);
char *check_command_is_exist(t_env *env, char	*cmd);

#endif
