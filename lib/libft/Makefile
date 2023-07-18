NAME:=libft.a
DEBUG=0
SOURCE:=$(addsuffix .c, $(addprefix ft_, \
isalpha isdigit isalnum isascii isprint toupper tolower \
strlen memset memcpy memmove strlcpy strlcat strchr strrchr strncmp memchr \
memcmp strnstr strdup \
bzero \
atoi calloc \
substr strjoin strtrim split itoa strmapi striteri \
$(addsuffix _fd, putchar putstr putendl putnbr) \
))
OBJECTS:=$(SOURCE:.c=.o)

COMPILER:=cc
COMPILER_FLAGS:=-Wall -Werror -Wextra
INCLUDES:=-I.

AR=ar -rcs
ifeq ($(DEBUG), 1)
	COMPILER_FLAGS+=-g
	AR=ar -rv
endif

all: $(NAME)

$(NAME): $(OBJECTS)
	$(AR) $@ $^

%.o: %.c
	$(COMPILER) $(COMPILER_FLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(NAME) $(OBJECTS)

fclean: clean

re: fclean all
