NAME = cub3d

LIB_DIR = lib
SRC_DIR = src
INC_DIR = inc

LIBFTALL_DIR = $(LIB_DIR)/libftall
LIBMLX_DIR = $(LIB_DIR)/mlx
LIBS = $(LIBFTALL_DIR)/libftall.a $(LIBMLX_DIR)/libmlx.a

LINK = -L$(LIBFTALL_DIR) -lftall -L$(LIBMLX_DIR) -lmlx
INC = -I$(INC_DIR) -I$(INC_DIR)/core -I$(LIBFTALL_DIR) -I$(LIBMLX_DIR)

ENGINE_SRC = $(addprefix $(SRC_DIR)/engine/, $(addsuffix .c, \
core colour events vector layers csketch \
))
ENGINE_OBJ = $(ENGINE_SRC:%.c=%.o)

MANDATORY_SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main parser parser_textures parser_rgb parser_map parser_utils \
))
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra
LINK += -framework OpenGL -framework AppKit
DEBUG = ""
ifeq ($(DEBUG),1)
	CFLAGS += -g
endif
COBJS = $(ENGINE_OBJ) $(MANDATORY_OBJ)

all: $(NAME)

$(NAME): $(LIBS) $(COBJS)
	cc $(CFLAGS) -DBUILD_MANDATORY $(INC) $(LINK) -o $@ $(COBJS)

%.o: %.c
	cc $(CFLAGS) $(INC) -o $@ -c $<

$(LIBS):
ifeq ($(DEBUG), 1)
	make DEBUG=1 -C $(LIBFTALL_DIR)
	make DEBUG=1 -C $(LIBMLX_DIR)
else
	make -C $(LIBFTALL_DIR)
	make -C $(LIBMLX_DIR)
endif

clean:
	rm -rf $(NAME) $(COBJS) *.dSYM

fclean: clean
	make fclean -C $(LIBFTALL_DIR)
	make clean -C $(LIBMLX_DIR)

re: fclean all
