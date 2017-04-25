NAME = minishell

SRC = sh.c sh_functions.c ft_cnt_words.c navigate_dirs.c echo.c environment_vars.c

OBJ = $(SRC:.c=.o)

LIB = libft/

SRC_DIR = src/

OPTS = -Wall -Werror -Wextra

all:
	@make -C $(LIB)
	@echo "---==== building project ====---"
	@gcc -c $(addprefix $(SRC_DIR), $(SRC)) $(OPTS) -Iincludes -Ilibft/includes
	@gcc -g -o $(NAME) $(OBJ) $(LIB)libftprintf.a

$(NAME): all

clean:
	@echo "---==== cleaning project ====---"
	@rm -f $(OBJ)
	@make clean -C $(LIB)

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIB)

re: fclean all
