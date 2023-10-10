NAME = cub3d

OS = $(shell uname)

LIB_DIR = lib
SRC_DIR = src
INC_DIR = inc

LIBFTALL_DIR = $(LIB_DIR)/libftall
LIBMLX_DIR = $(LIB_DIR)/mlx
LIBMLXLINUX_DIR = $(LIB_DIR)/mlx_linux
LIBS = $(LIBFTALL_DIR)/libftall.a $(LIBMLX_DIR)/libmlx.a $(LIBMLXLINUX_DIR)/libmlx_Linux.a

LINK = -L$(LIBFTALL_DIR) -lftall -L$(LIBMLX_DIR) -lmlx
LINKLINUX = -L$(LIBFTALL_DIR) -lftall -L$(LIBMLXLINUX_DIR) -lmlx_Linux
INC = -I$(INC_DIR) -I$(LIBFTALL_DIR) -I$(LIBMLX_DIR)
INCLINUX = -I$(INC_DIR) -I$(LIBFTALL_DIR) -I$(LIBMLXLINUX_DIR)

MANDATORY_SRC = $(ENGINE_SRC) $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main parser parser_textures parser_rgb parser_map parser_utils colour vector \
))
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra
LINK += -framework OpenGL -framework AppKit
LINKLINUX += -lXext -lX11 -lm -lz
DEBUG = ""
ifeq ($(DEBUG),1)
	CFLAGS += -g
endif

all: $(NAME)

$(NAME): $(LIBS) $(MANDATORY_OBJ)
ifeq ($(OS), Darwin)
	cc $(CFLAGS) -DBUILD_MANDATORY $(INC) $(LINK) -o $@ $(MANDATORY_OBJ)
else ifeq ($(OS), Linux)
	cc $(CFLAGS) -DBUILD_MANDATORY -o $@ $(MANDATORY_OBJ) $(INCLINUX) $(LINKLINUX)
endif

%.o: %.c
ifeq ($(OS), Darwin)
	cc $(CFLAGS) $(INC) -o $@ -c $<
else ifeq ($(OS), Linux)
	cc $(CFLAGS) $(INCLINUX) -o $@ -c $<
endif

$(LIBS):
ifeq ($(DEBUG), 1)
	make DEBUG=1 -C $(LIBFTALL_DIR)
ifeq ($(OS), Darwin)
	make DEBUG=1 -C $(LIBMLX_DIR)
endif
ifeq ($(OS), Linux)
	make DEBUG=1 -C $(LIBMLXLINUX_DIR)
endif
else
	make -C $(LIBFTALL_DIR)
ifeq ($(OS), Darwin)
	make -C $(LIBMLX_DIR)
endif
ifeq ($(OS), Linux)
	make -C $(LIBMLXLINUX_DIR)
endif
endif

clean:
	rm -rf $(NAME) $(MANDATORY_OBJ) *.dSYM

fclean: clean
	make fclean -C $(LIBFTALL_DIR)
ifeq ($(OS), Darwin)
	make clean -C $(LIBMLX_DIR)
else ifeq ($(OS), Linux)
	make clean -C $(LIBMLXLINUX_DIR)
endif

re: fclean $(NAME)