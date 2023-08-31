NAME = cub3d

LIB_DIR = lib
SRC_DIR = src
INC_DIR = inc

LIBFTALL_DIR = $(LIB_DIR)/libftall
LIBS = $(LIBFTALL_DIR)/libftall.a

SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main parse_textures parse_rgb))

LINK = -L$(LIBFTALL_DIR) -lftall
INC = -I$(INC_DIR) -I$(LIBFTALL_DIR)

DEBUG=""
CFLAGS = -Wall -Werror -Wextra
ifeq ($(DEBUG),1)
	CFLAGS += -g
endif

all: $(NAME)

$(NAME): $(LIBS)
	cc $(CFLAGS) $(INC) $(LINK) -o $@ $(SRC)

$(LIBS):
ifeq ($(DEBUG), 1)
	make DEBUG=1 -C $(LIBFTALL_DIR)
else
	make -C $(LIBFTALL_DIR)
endif

clean:
	rm -rf $(NAME) $(OBJS) *.dSYM

fclean: clean
	make fclean -C $(LIBFTALL_DIR)

re: fclean all
