NAME = libftall.a

LIBFT_DIR = libft
LIBFT_SRC = $(addprefix $(LIBFT_DIR)/, $(addprefix ft_, $(addsuffix .c,\
atoi bzero calloc isalnum isalpha isascii isdigit isprint itoa memchr memcmp \
memcpy memmove memset putchar_fd putstr_fd putnbr_fd putendl_fd split strchr \
strdup striteri strjoin strlcat strlcpy strlen strmapi strncmp strnstr strrchr \
strtrim substr tolower toupper)))

GNL_DIR = get_next_line
GNL_SRC = $(GNL_DIR)/get_next_line.c

PRINTF_DIR = ft_printf
PRINTF_SRC = $(addprefix $(PRINTF_DIR)/,\
$(addprefix ft_, $(addsuffix .c, printf vasprintf asprintf))\
$(addprefix core/, $(addsuffix .c, printf_core core_utils convert_args output_format flags)))

ADDONS_DIR = addons
ADDONS_SRC = $(addprefix $(ADDONS_DIR)/, $(addprefix ft_, $(addsuffix .c,\
strndup resize_str append_str_2d 2d_array_len free_str_2d vfree strdup_2d)))

SRC = $(LIBFT_SRC) $(ADDONS_SRC)
LIBFT_OBJS = $(SRC:.c=.o)
GNL_OBJS = $(GNL_SRC:.c=.o)
PRINTF_OBJS = $(PRINTF_SRC:.c=.o)

OBJS = $(LIBFT_OBJS) $(PRINTF_OBJS) $(GNL_OBJS)

cc = cc
cflags = -Wall -Werror -Wextra #-O2

DEBUG=""
ifeq ($(DEBUG), 1)
	cflags += -g #-fsanitize=address
endif

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(PRINTF_OBJS): %.o: %.c
	$(cc) $(cflags) -Ift_printf/core -o $@ -c $<

$(LIBFT_OBJS): %.o: %.c
	$(cc) $(cflags) -I. -o $@ -c $<

$(GNL_OBJS): %.o: %.c
	$(cc) $(cflags) -DBUFFER_SIZE=128 -I. -o $@ -c $<

clean:
	rm -rf $(NAME) $(OBJS)

fclean: clean

re: fclean all
