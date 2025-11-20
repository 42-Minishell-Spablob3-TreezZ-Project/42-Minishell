NAME = minishell

SRC = $(shell find ./src -name "*.c")
OBJ = $(SRC:.c=.o)

LIBFT_PATH = ./include/libft
LIBFT = $(LIBFT_PATH)/libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror -g

RM = rm -f

AR = ar rcs

all: $(LIBFT) $(NAME)

$(NAME): $(OBJ) $(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) -lreadline -L$(LIBFT_PATH) -lft -o $(NAME)

$(LIBFT):
		make -C $(LIBFT_PATH)

%.o: %.c
		@$(CC) $(CFLAGS) -c $< -o $@

clean:
		make -C $(LIBFT_PATH) clean
		$(RM) $(OBJ)

fclean: clean
		make -C $(LIBFT_PATH) fclean
		$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
