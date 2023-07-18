SHELL := bash

SRC = src/*.c

LIBFT = lib/libft
GNL = lib/get_next_line

GNL_SRC = $(shell find $(GNL) -type f -name 'get_next_line*.c')
GNL_OBJ = $(GNL_SRC:.c=.o)
GNL_COMP_FLAGS = -Wall -Werror -Wextra -I$(GNL) -DBUFFER_SIZE=64

INC = inc

LIBS = $(LIBFT)/libft.a
LINK_LIBS = -L$(LIBFT) -lft
HEADERS = -I$(INC) -I$(LIBFT) -I$(GNL)
FLAGS = -Wall -Werror -Wextra $(LINK_LIBS) $(HEADERS)

all: $(LIBS)
	gcc $(SRC) $(FLAGS) -o cub3d
	echo Good to go
	
$(LIBS):
	@clear
	@echo Compiling libft
	@make -s -C $(LIBFT)

	@echo Compiling get_next_line
	@-for i in $(GNL_SRC:%.c=%); do\
		gcc $$i.c $(GNL_COMP_FLAGS) -c -o $$i.o;\
	done
	@ar rcs $(LIBS) $(GNL_OBJ)

clean:
	clear
	rm -f cub3d
	rm -f $(GNL)/*.o
	make fclean -s -C $(LIBFT)
	echo nothing here anymore, well, except .c

fclean: clean

re: clean all