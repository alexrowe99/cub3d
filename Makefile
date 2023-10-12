NAME = cub3d

SRC_DIR = src
INC_DIR = inc

MLXGE = lib/MLXGE/libmlxge.a
INC = -I$(INC_DIR) -Ilib/MLXGE
LINK = -Llib/MLXGE -lmlxge

MANDATORY_SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main parser parser_textures parser_rgb parser_map parser_utils \
))
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

CFLAGS = -Wall -Werror -Wextra

OSLINK=
SET_OS=$(shell uname)
ifeq ($(SET_OS), Darwin)
	OSLINK=-framework OpenGL -framework AppKit
	SET_OS=SET_OS=1
else ifeq ($(SET_OS), Linux)
	OSLINK=
	SET_OS=SET_OS=2
endif

DEBUG=
ifeq ($(DEBUG),1)
	CFLAGS += -g
endif
COBJS = $(MANDATORY_OBJ)

all: $(NAME)

$(NAME): $(MLXGE) $(COBJS)
	cc $(CFLAGS) $(COBJS) $(INC) $(LINK) -o $@ $(OSLINK)

%.o: %.c
	cc $(CFLAGS) $(INC) -o $@ -c $<

$(MLXGE):
ifeq ($(DEBUG), 1)
	make -C lib/MLXGE $(SET_OS) DEBUG=1
else
	make -C lib/MLXGE $(SET_OS)
endif

clean:
	rm -rf $(NAME) $(COBJS) *.dSYM

fclean: clean
	make -C lib/MLXGE fclean

re: fclean all
