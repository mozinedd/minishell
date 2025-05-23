CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes -fsanitize=address

SRCS = srcs/parsing/command_line.c \
	srcs/parsing/syntax_error.c \
	srcs/parsing/tokens.c \
	srcs/parsing/ft_free.c \
	lib/ft_strncmp.c \
	srcs/parsing/cmd_to_send.c \
	srcs/parsing/expand_t_fille.c \
	lib/ft_substr.c \
	lib/ft_isalnum.c \
	srcs/parsing/main.c \
	srcs/parsing/expand_cmd.c \
	lib/ft_strjoin.c \
	srcs/parsing/remove_quotes.c
	

SRCSEXEC = lib/ft_lstnew.c \
	lib/ft_memcpy.c \
	lib/ft_strchr.c \
	lib/ft_strdup.c \
	lib/ft_strlen.c \
	lib/ft_strndup.c \
	srcs/execution/environment.c \


OBJS = $(SRCS:.c=.o)
OBJSEXEC = $(SRCSEXEC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(OBJSEXEC)
	$(CC) $(CFLAGS) $(OBJS) $(OBJSEXEC) -o $(NAME) -lreadline

%.o: %.c minishell.h
	$(CC) -c $(CFLAGS) $< -o $@

run:
	./$(NAME)

clean:
	rm -f $(OBJS) $(OBJSEXEC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

