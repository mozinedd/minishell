CC = cc

CFLAGS = -Wall -Wextra -Werror -I includes -fsanitize=address

SRCS = lib/ft_strncmp.c lib/ft_strtrim.c lib/ft_substr.c lib/ft_isalnum.c lib/ft_itoa.c lib/ft_strjoin.c lib/ft_split.c\
	 srcs/parsing/command_line.c\
	 srcs/parsing/expanding1.c srcs/parsing/expanding2.c srcs/parsing/expanding3.c\
	 srcs/parsing/export1.c srcs/parsing/export2.c srcs/parsing/export3.c\
	 srcs/parsing/fill_cmd1.c srcs/parsing/fill_cmd2.c\
	 srcs/parsing/final_cmd1.c srcs/parsing/final_cmd2.c srcs/parsing/final_cmd3.c\
	 srcs/parsing/ft_free.c \
	 srcs/parsing/ft_sp_space.c srcs/parsing/ft_sp_pipe2.c srcs/parsing/ft_sp_pipe1.c\
	 srcs/parsing/herdoc1.c  srcs/parsing/herdoc2.c \
	 srcs/parsing/is_fct.c \
	 srcs/parsing/tokens_1.c srcs/parsing/tokens_2.c srcs/parsing/tokens_3.c \
	 srcs/parsing/syntax_err1.c \
	 srcs/parsing/remove_quotes.c \
	 srcs/parsing/parse.c \
	 srcs/parsing/signal.c \
	srcs/parsing/main.c  

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

all: $(NAME) clean

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

