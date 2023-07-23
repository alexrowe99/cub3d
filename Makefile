# BASH EXECUTION FOR PATTERN MATCHING WITH FOR LOOP
# 	- COMPILES AND ARCHIVE GNL OBJECTS
SHELL := bash

SRC = $(shell find src -type file -name '*.c')
INC = inc
LIB = lib

LIBFT_DIR = $(LIB)/libft
PRINTF_DIR = $(LIB)/ft_printf
GNL_DIR = $(LIB)/get_next_line
MLX_DIR = $(LIB)/mlx

GNL_SRC = $(shell find $(GNL_DIR) -type f -name 'get_next_line*.c')
GNL_OBJ = $(GNL_SRC:.c=.o)

LIBS = $(LIBFT)/libft.a $(MLX_DIR)/libmlx.a $(PRINTF_DIR)/libftprintf.a
LINK_LIBS = -L$(LIBFT_DIR) -lft -L$(MLX_DIR) -lmlx -L$(PRINTF_DIR) -lftprintf

HEADERS = -I$(INC) -I$(LIBFT_DIR) -I$(GNL_DIR) -I$(MLX_DIR) -I$(PRINTF_DIR)

DEBUG = 0
ifeq ($(DEBUG), 1)
	FLAGS = -DDEBUG=1 -g
	GNL_COMP_FLAGS = -g
endif

FLAGS += -Wall -Werror -Wextra $(LINK_LIBS) $(HEADERS) -framework OpenGL -framework AppKit
GNL_COMP_FLAGS += -Wall -Werror -Wextra -I$(GNL_DIR) -DBUFFER_SIZE=64

DEFINE_OS = ""
ifeq ($(shell uname), Darwin)
	DEFINE_OS = -DMACOS=1
endif

all: $(LIBS)
ifeq ($(DEBUG), 1)
	cc $(DEFINE_OS) $(FLAGS) $(SRC) -o cub3d
else
	@cc $(DEFINE_OS) $(FLAGS) $(SRC) -o cub3d
	@echo Good to go
endif
	
$(LIBS):
	@clear
ifeq ($(DEBUG), 1)
	@make -C $(LIBFT_DIR) DEBUG=1
	@make -s -C $(PRINTF_DIR) DEBUG=1
	@-for i in $(GNL_SRC:%.c=%); do\
		echo "cc $$i.c $(GNL_COMP_FLAGS) -c -o $$i.o";\
		cc $$i.c $(GNL_COMP_FLAGS) -c -o $$i.o;\
	done
	ar -rcsv $(LIBFT_DIR)/libft.a $(GNL_OBJ)
	@make -C $(MLX_DIR) DEBUG=1
else
	@printf "Compiling libft\t\t\t"
	@make -s -C $(LIBFT_DIR)
	@printf "\e[0;92mDONE!\e[0m\n"
	@printf "Compiling printf\t\t\t"
	@make -s -C $(PRINTF_DIR)
	@printf "\e[0;92mDONE!\e[0m\n"
	@printf "Compiling get next line\t\t"
	@-for i in $(GNL_SRC:%.c=%); do\
		cc $$i.c $(GNL_COMP_FLAGS) -c -o $$i.o;\
	done
	@ar -rcs $(LIBFT_DIR)/libft.a $(GNL_OBJ)
	@printf "\e[0;92mDONE!\e[0m\n"
	@printf "Compiling mlx\t\t\t"
	@make -s -C $(MLX_DIR)
	@printf "\e[0;92mDONE!\e[0m\n"
endif

clean:
	@clear
	@rm -rf *.dSYM
	@rm -f cub3d
	@rm -f $(GNL_DIR)/*.o
	@make fclean -s -C $(LIBFT_DIR)
	@make fclean -s -C $(PRINTF_DIR)
	@make clean -s -C $(MLX_DIR)
	@echo nothing here anymore, well, except .c

fclean: clean

re: clean all