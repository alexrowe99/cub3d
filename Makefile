# ----- Cub3d Directories ------------------------------------------------------

SRC_DIR = src
INC_DIR = inc

# ----- Cub3d Dependencies -----------------------------------------------------

MLXGE = lib/MLXGE/libmlxge.a
INC = -I$(INC_DIR) -Ilib/MLXGE
LINK = -Llib/MLXGE -lmlxge

# ----- Cub3d Executables ------------------------------------------------------

NAME = cub3d
NAME_BONUS = cub3d_bonus

# ----- Mandatory C Files ------------------------------------------------------

MANDATORY_SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main initialise parser parser_textures parser_rgb parser_map parser_utils \
))
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

# ----- Bonus C Files ----------------------------------------------------------

BONUS_SRC = $(addprefix $(SRC_DIR)/bonus, $(addsuffix _bonus.c, \
# main initialise parser parser_textures parser_rgb parser_map parser_utils \
))
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

# ----- Compilation Flags ------------------------------------------------------

CFLAGS = -Wall -Werror -Wextra -O2

OSLINK =
DEF_OS =
SET_OS = $(shell uname)
ifeq ($(SET_OS), Darwin)
	OSLINK = -framework OpenGL -framework AppKit
	DEF_OS = -DBUILD_OS=1
else ifeq ($(SET_OS), Linux)
	INC += -I/usr/include
	LINK += -L/usr/lib
	OSLINK = -lXext -lX11 -lm -lz
	DEF_OS += -DBUILD_OS=2
endif
BUILD_OS = SET_OS=$(SET_OS)

DEBUG =
ifeq ($(DEBUG),1)
	CFLAGS += -g -fsanitize=address
endif

# ----- Build Rules ------------------------------------------------------------

# 	all - Defaults to mandatory build.
all: $(NAME)

$(NAME): mandatory

#	m - Builds the mandatory section.
mandatory: $(MLXGE) $(MANDATORY_OBJ)
	cc $(CFLAGS) $(MANDATORY_OBJ) $(DEF_OS) $(INC) $(LINK) -o $(NAME) $(OSLINK)

$(MANDATORY_OBJ): %.o: %.c
	cc $(CFLAGS) $(DEF_OS) $(INC) -o $@ -c $<

# 	b - Builds the bonus section

# bonus: set_build_bonus $(NAME_BONUS)

# set_build_bonus:

# $(NAME): $(MLXGE) $(COBJS)
# cc $(CFLAGS) $(COBJS) $(INC) $(LINK) -o $@ $(OSLINK)

# ------------------------------------------------------------------------------

$(MLXGE):
ifeq ($(DEBUG), 1)
	make -C lib/MLXGE $(BUILD_OS) DEBUG=1
else
	make -C lib/MLXGE $(BUILD_OS)
endif

clean:
	rm -rf $(NAME) $(MANDATORY_OBJ) *.dSYM

fclean: clean
	make -C lib/MLXGE fclean

re: fclean all
