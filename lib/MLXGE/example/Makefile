NAME=example

MLXGE=../libmlxge.a

LINK=""
BUILD_OS=$(shell uname)
ifeq ($(BUILD_OS), Darwin)
	LINK=-framework OpenGL -framework AppKit
	BUILD_OS=-DBUILD_OS=1
endif

SRCS = example.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLXGE)
	cc -Wall -Werror -Wextra -L../ -lmlxge $(OBJS) -o $@ $(LINK)

$(OBJS): %.o: %.c
	cc -Wall -Werror -Wextra $(BUILD_OS) -I../ -c $< -o $@

$(MLXGE):
	make -C ../

clean:
	rm -rf $(NAME) *.o

fclean: clean
	make -C ../ fclean

re: fclean all
