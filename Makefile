CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes 

SRCS = 
# srcs/parsing/command_line.c \
# srcs/parsing/syntax_error.c \
# srcs/parsing/tokens.c \
# srcs/parsing/ft_free.c \
# lib/ft_strncmp.c \
# srcs/parsing/cmd_to_send.c \
# lib/ft_substr.c

SRCSEXEC = lib/ft_atoi.c \
	lib/ft_isdigit.c \
	lib/ft_memcpy.c \
	lib/ft_memset.c \
	lib/ft_calloc.c \
	lib/ft_putchar.c \
	lib/ft_strchr.c \
	lib/ft_strdup.c \
	lib/ft_strlen.c \
	lib/ft_strndup.c \
	lib/ft_strcmp.c \
	lib/ft_split.c \
	lib/ft_strcpy.c \
	srcs/execution/built_in/env.c\
	srcs/execution/built_in/cd.c\
	srcs/execution/built_in/echo.c\
	srcs/execution/built_in/exit.c\
	srcs/execution/built_in/export.c\
	srcs/execution/built_in/pwd.c\
	srcs/execution/main.c\
	srcs/execution/single_commands/handle_single_command.c\
	srcs/execution/utilis/is_builtin.c \
	srcs/execution/utilis/help.c \
	lib/ft_strncmp.c\
	lib/ft_isalpha.c\
	lib/ft_isalnum.c \
	srcs/execution/update_exit_status.c\
	srcs/execution/built_in/unset.c \
	lib/ft_substr.c \
	lib/ft_strjoin.c \
	srcs/execution/utilis/ft_getenv.c \
	srcs/execution/main_excute_cmd.c
	

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
