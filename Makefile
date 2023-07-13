SRC = src/*.c


INC = inc
LIB_DIR = lib

LIBS = -L$(LIB_DIR)/libft -lft -L$(LIB_DIR)/mlx -lmlx
HEADERS = -I$(INC) -I$(LIB_DIR)/libft -I$(LIB_DIR)/mlx
FLAGS = -Wall -Werror -Wextra $(LIBS) $(HEADERS) -framework OpenGL -framework AppKit

all:
	@clear
	@make -s -C $(LIB_DIR)/libft
	@echo Compiling libft
	@make -s -C $(LIB_DIR)/mlx
	@echo Compiling mlx
	@gcc $(SRC) $(FLAGS) -o cub3d
	@echo Good to go
	

clean:
	@clear
	@rm -f cub3d
	@make fclean -s -C $(LIBFT)
	@echo nothing here anymore, well, except .c

fclean: clean

re: clean all