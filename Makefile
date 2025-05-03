CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes 

SRCS = srcs/parsing/command_line.c \
	srcs/parsing/syntax_error.c \
	srcs/parsing/tokens.c \
	srcs/parsing/main.c \
	srcs/parsing/ft_free.c \
	lib/ft_strncmp.c \
	lib/ft_substr.c

SRCSEXEC = lib/ft_lstnew.c \
	lib/ft_memcpy.c \
	lib/ft_strchr.c \
	lib/ft_strdup.c \
	lib/ft_strlen.c \
	lib/ft_strndup.c \
	srcs/execution/environment.c \
	srcs/execution/main.c


OBJS = $(SRCS:.c=.o)
OBJSEXEC = $(SRCSEXEC:.c=.o)

NAME = minishell

all: $(NAME)

$(NAME): $(OBJS) $(OBJSEXEC)
	$(CC) $(CFLAGS) $(OBJS) $(OBJSEXEC) -o $(NAME) -lreadline

%.o: %.c minishell.h
	$(CC) -c $(CFLAGS) $< -o $@
	
clean:
	rm -f $(OBJS) $(OBJSEXEC)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

