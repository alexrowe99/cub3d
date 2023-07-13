SRC = src/*.c


LIBFT = libft
INC = inc

LIBS = -L$(LIBFT) -lft
HEADERS = -I$(INC) -I$(LIBFT)
FLAGS = -Wall -Werror -Wextra $(LIBS) $(HEADERS)

all:
	@clear
	@make -s -C $(LIBFT)
	@echo Compiling libft
	@gcc $(SRC) $(FLAGS) -o cub3d
	@echo Good to go
	

clean:
	@clear
	@rm -f cub3d
	@make fclean -s -C $(LIBFT)
	@echo nothing here anymore, well, except .c

fclean: clean

re: clean all