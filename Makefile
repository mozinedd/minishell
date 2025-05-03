CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes

SRCS = \
	lib/ft_substr.c \
	srcs/parsing/command_line.c \
	srcs/parsing/syntax_error.c \
	srcs/parsing/tokens.c \
	srcs/parsing/mainc.c \
	srcs/parsing/ft_fre.c


SRCSEXEC =	lib/ft_lstnew.c lib/ft_memcpy.c lib/ft_strchr.c lib/ft_strdup.c lib/ft_strlen.c lib/ft_strndup.c \
			srcs/execution/environment.c srcs/execution/main.c

OBJS = $(SRCS:.c=.o)
OBJSEXEC = $(SRCSEXEC:.c=.o)
NAME = minishell
all: $(NAME)

$(NAME): $(OBJS) $(OBJSEXEC)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
%.o:%.c 
	cc -c $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all

# .PHONY: all clean fclean re
