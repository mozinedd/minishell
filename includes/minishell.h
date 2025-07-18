/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysouaf <ysouaf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 21:05:21 by ysouaf            #+#    #+#             */
/*   Updated: 2025/07/18 21:05:19 by ysouaf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <stdbool.h>
# include <sys/ioctl.h>
# include <stdarg.h>
# include <termios.h>

# define HEREDOC_MODE 16
# define CTRL_C 1

typedef enum e_token_type
{
	WORD,
	HERDOC,
	APPEND,
	REDIR_IN,
	REDIR_OUT,
	PIPE
}	t_token_type;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_tokens
{
	char				*str;
	t_token_type		type;
	struct s_tokens		*next;
}	t_tokens;

typedef struct s_file
{
	t_token_type	type;
	char			*value;
	int				found_quts;
	int				fd;
}	t_file;

typedef struct s_cmds
{
	char			**cmd;
	t_file			*file;
	struct s_cmds	*next;
	struct s_cmds	*prev;
}	t_cmds;

typedef struct s_glob
{
	t_cmds			*cmd;
	t_env			*env;
	t_tokens		*token;
	int				exit_status;
	int				in_double_quotes;
	struct termios	origin;
}	t_glob;

typedef struct s_gc
{
	void			*ptr;
	struct s_gc		*next;
}	t_gc;

typedef struct s_cd
{
	void			*ptr;
	struct s_cd		*next;
}	t_cd;

extern int	g_sig_hander;

/* Libft */
int			ft_isalpha(char c);
char		**ft_split(char *s, char c);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_strtrim(char *s1, char *set);
int			ft_isdigit(char c);
char		*ft_itoa(int n);
char		*ft_strchr(const char *s, int c);
size_t		ft_strlen(const char *str);
char		*ft_strndup(const char *s, size_t n);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
char		*ft_substr(char const *s, unsigned int start, size_t len);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_isalnum(char c);

/* Parsing */
char		*read_command_line(void);
t_gc		**get_garbage_collector(void);
void		*gc_malloc(size_t size);
void		gc_free(void);

/* Tokens */
t_tokens	*new_token(char *str, t_token_type type);
void		add_token(t_tokens **token, t_tokens *new);
void		handl_op(char *str, int *i, t_tokens **token);
t_tokens	*append_token_list(t_tokens *list1, t_tokens *list2);
int			valid_quotes(char *s);
t_tokens	*tokenize_cmd(char *line);
t_tokens	*tokenize_all_segments(char **lines);
t_tokens	*lexer(char *line, t_glob *global);
void		skip_to_next(char *str, int *i);

/* Syntax error */
bool		check_redirections(t_tokens *t);
bool		check_pipe_error(char *line);
bool		redir_error(void);
bool		pipe_error(void);

/* is_ functions */
int			is_space(char c);
int			is_quote(char c);
int			is_redirection(t_tokens *type);
int			is_operator(char c);

/* split */
char		**ft_split_whitespace(char *s);
char		**split_by_pipes(char *line);
size_t		count_pipes(char *line);
char		*trim_spaces(char *str);
size_t		count_word(char *s, char c);

/* Signals */
void		handle_signal(int sig);
void		init_signals(void);

/* Heredoc */
int			creat_herdoc(char *delimiter, t_glob *global,
				int fd_read, int flag);
int			open_heredoc(t_glob *global);
void		close_heredoc(t_glob *global);

/* Export */
char		**trim_split_result(char **arr);
int			red(char *str);
int			there_is(char *str, char c);
int			process_export_arg(char **sp, int i, int flag2);
int			handle_export_command(char **sp, int i, int flag2);
char		**operate_export(char **lines);

/* Expanding */
char		*get_env_value(char *varname, t_env *envp);
char		*allocate_name_var(char *wrd, int *i);
char		*replace_word(char *word, int start, int end, char *replace);
char		*replace_quts(char *val);
char		*expand_from_to(char *word, int start, int *end, t_glob *g);
char		*expan_word(char *wrd, t_glob *global);
int			expand_var(t_file *file, t_glob *global);
char		*expand_loop(char *word, int *i, int *end, t_glob *g);
char		*herdoc_expand(char *word, int start, int *end, t_glob *g);

/* Final command */
char		*join_commands(t_glob *global);
int			size_cmd(char *expanded_word);
char		**fill_command(char *joined_str);
t_file		*init_files_of_commands(t_tokens *token);
int			fill_files(t_file *files, t_glob *global);
t_cmds		*init_command_node(void);
t_cmds		*create_commands(t_glob *global);
t_cmds		*return_quts(t_cmds **command);
t_cmds		*final_commandes(t_cmds **command);
int			has_quotes(char *str);
char		*remove_quts(char *line);

/* Terminal */
void		get_terminal(struct termios *termios);
void		set_terminal(struct termios *termios);

/* Parse function */
t_cmds		*parsing(t_glob *global);
t_glob		*init_global_struct(void);
int			mshll_loop(char **envp);

/* Execution */
char		*ft_strdup(char *s1);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		ft_putchar(char c);
int			ft_atoi(const char *str);
char		*ft_strcpy(char *dest, char *src);
void		*ft_memset(void *b, int c, size_t len);
void		*ft_calloc(size_t count, size_t size);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_print_str(char *str);
int			ft_printf(const char *format, ...);
int			ft_putnbr(int nb);
int			ft_putchar_exec(char c);

int			ft_cd(t_env *env, char **args);
int			ft_echo(char **args);
int			ft_exit(char **args);
void		ft_pwd(t_env *env);
void		ft_env(t_env *env);
void		ft_export(t_env **env, char **cmd);
int			ft_unset(char **args, t_env **env);

void		handle_single_command(t_glob *global);
void		handle_multiple_command(t_glob *global);
void		execute_command(t_glob *global);
int			redirection_handel(t_file *tmp);
int			check_is_builtin(t_cmds *cmd);
int			exec_is_builtin(t_env **env, t_cmds *cmd);
t_env		*list_of_env(char **env);
char		**env_to_array(t_env *head);
char		*get_command_path(t_env *env, char *cmd);
int			exit_status(int status, int is_get);
int			detect_overflow(int is_set, int my_status);
char		*ft_getenv(t_env *env, const char *key);
char		*check_command_is_exist(t_env *env, char *cmd);
int			get_status_code(int status);
void		print_exported_vars(t_env *env);
t_env		*creat_new_var(char *key, char *value, char *key_val);
void		add_var_env(t_env **env, char *key, char *value, char *key_val);
t_env		*is_exist(t_env *env, char *key);
void		update_value(t_env **env, char *value, int is_append);
void		save_fd(int *in, int *out);
void		restore_fd(int *in, int *out);

#endif
