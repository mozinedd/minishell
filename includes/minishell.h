#ifndef MINISHELL_H
#define MINISHELL_H


#include <stdio.h>
#include <stdlib.h>
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


#define HEREDOC_MODE 16
#define CTRL_C 1

typedef enum e_token_type {
    WORD,       // string 
    HERDOC,     // <<
    APPEND,     // >>
    REDIR_IN,   // <
    REDIR_OUT,  // >
    PIPE     // |
} t_token_type;

// ls -la >> a > b < Makefile

typedef struct s_env {
	char *key;
	char *value;
	struct s_env *next;
} t_env;
typedef struct s_tokens{
    char *str;
    t_token_type type;
    struct s_tokens *next;
}   t_tokens;

typedef struct s_file
{
	t_token_type type;
	char *value;
	int found_quts;
	int fd;
} t_file;


typedef struct s_cmds
{
	char **cmd;
	t_file *file;
	struct s_cmds *next;
	struct s_cmds *prev;
} t_cmds;


/// @brief  here may  be error
typedef struct s_glob
{
	t_cmds *cmd;
	t_env *env;
	t_tokens *token;
	int exit_status;
	int in_double_quotes;
} t_glob;

/*==========execution=============*/


/*========global variable=========*/
extern int g_sig_hander;

/*================********================*/
/*				libft                	  */
/*================********================*/
int			ft_isalpha(char c);
char		**ft_split(char *s, char c);
char		*ft_strjoin2(char  *s1, char  *s2);
char		*ft_strtrim(char  *s1, char *set);
int 		ft_isdigit(char c);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
size_t 		ft_strlen(const char *str);
char 		*ft_strndup(const char *s, size_t n);
size_t		ft_strlcpy(char *dst,char *src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_isalnum(char c);

/*================********================*/
/*				parsing                	  */
/*================********================*/

/*****************|  readlines |***************/
char	*read_command_line(t_glob *global);

/*****************|  tokens  |***************/
t_tokens	*new_token(char *str, t_token_type type);
void		add_token(t_tokens **token, t_tokens *new);
void		handl_op(char *str, int *i, t_tokens **token);
t_tokens	*append_token_list(t_tokens *list1, t_tokens *list2);
int			valid_quotes(char *s);
t_tokens	*tokenize_cmd(char *line);
t_tokens	*tokenize_all_segments(char **lines);
t_tokens	*lexer(char *line, t_glob *global);
void 		skip_to_next(char *str, int *i);;

/*****************| syntaxe_error |***************/
bool		check_redirections(t_tokens *t);
bool		check_pipe_error(char *line);
bool		redir_error(void);
bool		pipe_error(void);


/******************|  is_functions  |***************/
int 		is_space(char c);
int 		is_quote(char c);
int			is_redirection(t_tokens *type);
int 		is_operator(char c);

/******************|  split  |***************/
char		**ft_split_whitespace(char *s);
char		**split_by_pipes(char *line);
size_t 		count_pipes(char *line);
void 		safe_free(char **arr, size_t idx);
char		*trim_spaces(char *str);

/******************|  signals  |********************/
void		handle_signal(int sig);
void 		init_signals();

/******************|  herdoc  |********************/
int			creat_herdoc(char *delimiter, t_glob *global, int fd_read, int flag);
int			open_heredoc(t_glob *global);
void		close_heredoc(t_glob *global);

/******************|  free  |********************/
void		free_tokens(t_tokens *token);
void		free_commands(t_cmds *commands);
void		free_split(char **tab);

/******************|  export  |********************/
char 		**trim_split_result(char **arr);
int 		red(char *str);
int 		there_is(char *str, char c);
int 		handle_export_command(char **sp, int i, int flag2);
char 		**operate_export(char **lines);

/******************|  expanding  |********************/
char		*get_env_value(char *varname, t_env *envp);
char		*allocate_name_var(char *wrd, int *i);
char		*replace_word(char *word, int start, int end, char *replace);
char		*replace_quts(char *val);
char		*expand_from_to(char *word, int start, int *end, t_glob *g);
char		*expan_word(char *wrd, t_glob *global);
int			expand_var(t_file *file, t_glob *global);

/******************|  final command   |********************/
char 		*join_commands(t_glob *global);
int			size_cmd(char *expanded_word);
char		**fill_command(char *joined_str);
t_file		*init_files_of_commands(t_tokens *token);
int			fill_files(t_file *files, t_glob *global);
t_cmds	*init_command_node(void);
t_cmds	*create_commands(t_glob *global);
t_cmds	*return_quts(t_cmds **command);
t_cmds	*final_commandes(t_cmds **command);
int			has_quotes(char *str);
char		*remove_quts(char *line);
void		cleanup_and_free(t_cmds *head, t_cmds *new_node);

/******************|  parse function   |********************/
t_cmds	*parsing(t_glob *global);
t_glob		*init_global_struct(void);
int			mshll_loop(char **envp);

/*================********================*/
/*				execution              	  */
/*================********================*/

char			*ft_strchr(const char *s, int c);
char			*ft_strndup(const char *s, size_t n);
char	*ft_strdup(char *s1);
void	ft_env(t_env *env);
size_t			ft_strlen(const char *str);
void    *ft_memcpy(void *dst, const void* src, size_t n);
void    ft_putchar(char c);
int	ft_atoi(const char *str);
void handle_single_command (t_glob *global);
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
void	ft_export (t_env **env, char **cmd);
int exit_status(int status, int is_get);
int ft_unset(char **args, t_env **env);
char    *ft_strjoin(char const *s1, char const *s2);
int		detect_overflow(int is_set, int my_status);
// todo : come back here
char *ft_getenv(t_env *env, const char *key);
char *check_command_is_exist(t_env *env, char	*cmd);
void execute_command(t_glob *global);

#endif
