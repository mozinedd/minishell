CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes 

SRCS = srcs/parsing/ft_strdup.c \
	srcs/parsing/ft_substr.c \
	srcs/parsing/command_line.c \
	srcs/parsing/syntax_error.c \
	srcs/parsing/tokens.c \
	srcs/parsing/main.c \
	srcs/parsing/ft_free.c \
	srcs/parsing/ft_strncmp.c \

OBJS = $(SRCS:.c=.o)
NAME = minishell
all: $(NAME)

$(NAME): $(OBJS) 
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
%.o:%.c 
	cc -c $(CFLAGS) $< -o $@
clean:
	rm -f $(OBJS)

fclean: clean 
	rm -f $(NAME)

re: fclean all

# .PHONY: all clean fclean re
