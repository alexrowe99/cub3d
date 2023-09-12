NAME = cub3d

LIB_DIR = lib
SRC_DIR = src
INC_DIR = inc

LIBFTALL_DIR = $(LIB_DIR)/libftall
LIBMLX_DIR = $(LIB_DIR)/mlx
LIBS = $(LIBFTALL_DIR)/libftall.a $(LIBMLX_DIR)/libmlx.a

LINK = -L$(LIBFTALL_DIR) -lftall -L$(LIBMLX_DIR) -lmlx
INC = -I$(INC_DIR) -I$(LIBFTALL_DIR) -I$(LIBMLX_DIR)

MANDATORY_SRC = $(ENGINE_SRC) $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main parser parser_textures parser_rgb parser_map parser_utils colour vector \
))

CFLAGS = -Wall -Werror -Wextra
LINK += -framework OpenGL -framework AppKit
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
	make DEBUG=1 -C $(LIBMLX_DIR)
else
	make -C $(LIBFTALL_DIR)
	make -C $(LIBMLX_DIR)
endif

clean:
	rm -rf $(NAME) $(OBJS) *.dSYM

fclean: clean
	make fclean -C $(LIBFTALL_DIR)
	make clean -C $(LIBMLX_DIR)

re: fclean mandatory
