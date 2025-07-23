CC = cc
CFLAGS = -Wall -Wextra -Werror -I includes #-g -fsanitize=address

SRCS = lib/ft_strncmp.c lib/ft_strtrim.c lib/ft_substr.c lib/ft_isalnum.c lib/ft_itoa.c lib/ft_strjoin2.c lib/ft_split.c\
	 srcs/parsing/command_line.c\
	 srcs/parsing/expanding1.c srcs/parsing/expanding2.c srcs/parsing/expanding3.c\
	 srcs/parsing/export1.c srcs/parsing/export2.c srcs/parsing/export3.c\
	 srcs/parsing/fill_cmd1.c srcs/parsing/fill_cmd2.c\
	 srcs/parsing/final_cmd1.c srcs/parsing/final_cmd2.c srcs/parsing/final_cmd3.c\
	 srcs/parsing/ft_sp_space.c srcs/parsing/ft_sp_pipe2.c srcs/parsing/ft_sp_pipe1.c\
	 srcs/parsing/herdoc1.c  srcs/parsing/herdoc2.c \
	 srcs/parsing/is_fct.c \
	 srcs/parsing/tokens_1.c srcs/parsing/tokens_2.c srcs/parsing/tokens_3.c \
	 srcs/parsing/syntax_err1.c \
	 srcs/parsing/remove_quotes.c \
	 srcs/parsing/parse.c \
	 srcs/parsing/signal.c  lib/ft_malloc.c lib/ft_free.c\
	 main.c srcs/parsing/terminal.c

SRCSEXEC = lib/ft_atoi.c\
	lib/ft_memcpy.c \
	lib/ft_memset.c \
	lib/ft_calloc.c \
	lib/ft_putchar.c \
	lib/ft_strchr.c \
	lib/ft_strdup.c \
	lib/ft_strlen.c \
	lib/ft_strndup.c \
	lib/ft_strcmp.c \
	lib/ft_strcpy.c \
	srcs/execution/built_in/env.c\
	srcs/execution/built_in/cd.c\
	srcs/execution/built_in/echo.c\
	srcs/execution/built_in/exit.c\
	srcs/execution/built_in/export/export.c\
	srcs/execution/built_in/pwd.c\
	srcs/execution/single_commands/handle_single_command.c \
	srcs/execution/utilis/is_builtin.c \
	srcs/execution/utilis/help.c \
	srcs/execution/update_exit_status.c\
	srcs/execution/built_in/unset.c \
	lib/ft_strjoin.c \
	srcs/execution/utilis/ft_getenv.c \
	srcs/execution/main_excute_cmd.c \
	srcs/execution/multi_commands/multi_commands.c \
	lib/ft_printf/ft_print_str.c \
	lib/ft_printf/ft_printf.c \
	lib/ft_printf/ft_putnbr.c\
	srcs/execution/utilis/list_of_env.c\
	srcs/execution/built_in/export/helper_export.c \
	srcs/execution/multi_commands/kill_pids.c

	

OBJS = $(SRCS:.c=.o)
OBJSEXEC = $(SRCSEXEC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(OBJSEXEC)
	$(CC) $(CFLAGS) $(OBJS) $(OBJSEXEC) -o $(NAME) -lreadline
%.o: %.c minishell.h
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -rf $(OBJS) $(OBJSEXEC)

fclean: clean
	rm -rf $(NAME)


re: fclean all

.PHONY: all clean fclean re
