
CC = cc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address

NAME = parsing

LIBFT_DIR = ../../libft

LIBFT_A = $(LIBFT_DIR)/libft.a

INCLUDES = -I../../includes -I$(LIBFT_DIR)

SRC = command_line.c main.c tokens.c ft_free.c syntax_error.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(LIBFT_A):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_A) -o $(NAME) $(INCLUDES) -lreadline

clean:
	make -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	make -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

