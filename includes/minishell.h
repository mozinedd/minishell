#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>  
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/ioctl.h>



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
    int fd;
    int found_quts;
} t_file;

typedef struct s_commands {
    char **cmd;        
    t_file *file;
    struct s_commands *next;
} t_commands;

typedef struct s_tokens{
    char *str;
    t_token_type type;
    struct s_tokens *next;
}   t_tokens;

typedef struct s_environment {
	char *key;
	char *value;
	struct s_environment *next;
} t_environment;

//========global variable=========//
extern int g_sig_hander;


/*================signals================*/
void	handle_signal(int sig);
void init_signals();


/*================parsing================*/
//command line functions
char *read_command_line();


/*================herdoc================*/
void	search_herdoc(t_commands **command, t_environment *env);
char	*ft_itoa(int n);


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
int	ft_isalnum(char c);
int	ft_isalpha(char c);
int is_space(char c);
char	**ft_split(char *s, char c);
char	*ft_strjoin(char  *s1, char  *s2);

//free
void free_token(t_tokens *token);
void free_commands(t_commands *commands);


//commandes
t_commands *create_commands(t_tokens *token, t_environment *env);
char *join_commands(t_tokens **token, t_environment *env);
char **fill_command(char *joined_str);
char *remove_quts(char *line);
int size_cmd(char *expanded_word);
t_commands *final_commandes(t_commands **command);

//expand
int expand_var(t_file *file, t_environment *envp);
char *get_env_value(char *varname, t_environment *envp);
char *allocate_name_var(char *wrd, int *i);
char *replace_word(char *word, int start, int end, char *replace);
char *expand_from_to(char *word, int start, int *end, t_environment *envp);
char *expan_word(char *wrd, t_environment *envp);


/*==========execution=============*/

char			*ft_strchr(const char *s, int c);
char			*ft_strndup(const char *s, size_t n);
char	*ft_strdup(char *s1);
t_environment	*ft_lstnew(void *content);
t_environment 	*list_of_env(char **env);
t_environment 	*creat_node(char *env);
size_t			ft_strlen(const char *str);
void    *ft_memcpy(void *dst, const void* src, size_t n);

#endif
