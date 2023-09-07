NAME = cub3d

LIB_DIR = lib
SRC_DIR = src
INC_DIR = inc

LIBFTALL_DIR = $(LIB_DIR)/libftall
LIBS = $(LIBFTALL_DIR)/libftall.a

LINK = -L$(LIBFTALL_DIR) -lftall
INC = -I$(INC_DIR) -I$(LIBFTALL_DIR)

MANDATORY_SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main parser parser_textures parser_rgb parser_map parser_utils colour))

CFLAGS = -Wall -Werror -Wextra
DEBUG = ""
ifeq ($(DEBUG),1)
	CFLAGS += -g
endif

all: $(NAME)

mandatory: $(LIBS)
	cc $(CFLAGS) -DBUILD_MANDATORY $(INC) $(LINK) -o $(NAME) $(MANDATORY_SRC)

$(NAME): $(LIBS)
	cc $(CFLAGS) $(INC) $(LINK) -o $@ $(MANDATORY_SRC)

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
