NAME = libftprintf.a

DEBUG = 0
ifeq ($(DEBUG), 1)
	FLAGS = -g
	AR = ar -rcvs
else
	AR = ar -rcs
endif

SOURCE = $(addsuffix .c, $(addprefix ft_,\
printf\
))
OBJECTS = $(SOURCE:.c=.o)

FLAGS += -Wall -Werror -Wextra
INCLUDES = -I.

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $@ $^

%.o: %.c
	cc $(FLAGS) $(INCLUDES) -o $@ -c $<

clean:
	rm -rf $(NAME)
	rm -rf $(OBJECTS)

fclean: clean

re: fclean all
