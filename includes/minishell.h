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


#define HEREDOC_MODE 16
#define CTRL_C 1

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


typedef struct s_tokens
{
	char *str;
	t_token_type type;
	struct s_tokens *next;
} t_tokens;

typedef struct s_commands
{
	char **cmd;
	t_file *file;
	struct s_commands *next;
} t_commands;

typedef struct s_environment
{
	char *key;
	char *value;
	struct s_environment *next;
} t_environment;

typedef struct s_glob
{
	t_commands *cmd;
	t_environment *env;
	t_tokens *token;
	int exit_status;
	int in_double_quotes;
} t_glob;

/*========global variable=========*/
extern int g_sig_hander;

/*================********================*/
/*				libft                	  */
/*================********================*/
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalnum(char c);
int			ft_isalpha(char c);
char		**ft_split(char *s, char c);
char		*ft_strjoin(char  *s1, char  *s2);
char		*ft_strtrim(char  *s1, char *set);
int 		ft_isdigit(char c);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
size_t 		ft_strlen(const char *str);
char 		*ft_strndup(const char *s, size_t n);
char		*ft_strdup(char *s1);
size_t		ft_strlcpy(char *dst,char *src, size_t dstsize);

/*================********================*/
/*				parsing                	  */
/*================********================*/

/*****************|  readlines |***************/
char		*read_command_line(t_glob *global, int exit_stat);

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
bool		check_redirections(t_tokens *t, t_glob *g);
bool		check_pipe_error(char *line, t_glob *g);
bool		redir_error(t_glob *g);
bool		pipe_error(t_glob *g);


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
void		free_commands(t_commands *commands);
void		free_split(char **tab);

/******************|  export  |********************/
char 		**trim_split_result(char **arr);
int 		red(char *str);
int 		there_is(char *str, char c);
int 		handle_export_command(char **sp, int i, int flag2);
char 		**operate_export(char **lines);

/******************|  expanding  |********************/
char		*get_env_value(char *varname, t_environment *envp);
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
t_commands	*init_command_node(void);
t_commands	*create_commands(t_glob *global);
t_commands	*return_quts(t_commands **command);
t_commands	*final_commandes(t_commands **command);
int			has_quotes(char *str);
char		*remove_quts(char *line);
void		cleanup_and_free(t_commands *head, t_commands *new_node);

/******************|  parse function   |********************/
t_commands	*parsing(t_glob *global);
t_glob		*init_global_struct(void);
int			mshll_loop(char **envp);

/*================********================*/
/*				execution              	  */
/*================********================*/

t_environment	*ft_lstnew(void *content);
t_environment 	*list_of_env(char **env);
t_environment 	*creat_node(char *env);
void    		*ft_memcpy(void *dst, const void* src, size_t n);
#endif
