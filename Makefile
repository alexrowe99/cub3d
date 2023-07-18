SHELL := bash

SRC = src/*.c
INC = inc
LIB = lib

LIBFT_DIR = $(LIB)/libft
GNL_DIR = $(LIB)/get_next_line
MLX_DIR = $(LIB)/mlx

GNL_SRC = $(shell find $(GNL_DIR) -type f -name 'get_next_line*.c')
GNL_OBJ = $(GNL_SRC:.c=.o)
GNL_COMP_FLAGS = -Wall -Werror -Wextra -I$(GNL_DIR) -DBUFFER_SIZE=64

LIBS = $(LIBFT)/libft.a $(MLX_DIR)/libmlx.a
LINK_LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx

HEADERS = -I$(INC) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR)
FLAGS = -Wall -Werror -Wextra $(LINK_LIBS) $(HEADERS) -framework OpenGL -framework AppKit

all: $(LIBS)
	@gcc $(SRC) $(FLAGS) -o cub3d
	@echo Good to go
	
$(LIBS):
	@clear
	@echo Compiling libft
	@make -s -C $(LIBFT_DIR)

	@echo Compiling get_next_line
	@-for i in $(GNL_SRC:%.c=%); do\
		gcc $$i.c $(GNL_COMP_FLAGS) -c -o $$i.o;\
	done
	@ar rcs $(LIBFT_DIR)/libft.a $(GNL_OBJ)

	echo Compiling mlx
	make -s -C $(MLX_DIR)

clean:
	@clear
	@rm -f cub3d
	@rm -f $(GNL_DIR)/*.o
	@make fclean -s -C $(LIBFT_DIR)
	@echo nothing here anymore, well, except .c

fclean: clean

re: clean all