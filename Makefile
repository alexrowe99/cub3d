# ----- Cub3d Directories ------------------------------------------------------

SRC_DIR = src
INC_DIR = inc
BONUS_SRC_DIR = src/bonus

# ----- Cub3d Dependencies -----------------------------------------------------

MLXGE = lib/MLXGE/libmlxge.a
INC = -I$(INC_DIR) -Ilib/MLXGE
LINK = -Llib/MLXGE -lmlxge

# ----- Cub3d Executables ------------------------------------------------------

NAME = cub3d
NAME_BONUS = cub3d_bonus

# ----- Cub3d shared names -----------------------------------------------------

SHARED_FILENAMES = initialise destroy parser parser_textures parser_rgb parser_map parser_utils

# ----- Cub3d core src ---------------------------------------------------------

CUB3D_SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, \
main display utils \
))
CUB3D_OBJ = $(CUB3D_SRC:%.c=%.o)

# ----- Mandatory C Files ------------------------------------------------------

MANDATORY_SRC = $(addprefix $(SRC_DIR)/, $(addsuffix .c, $(SHARED_FILENAMES) \
))
MANDATORY_OBJ = $(MANDATORY_SRC:%.c=%.o)

# ----- Bonus C Files ----------------------------------------------------------

BONUS_SRC = $(addprefix $(BONUS_SRC_DIR)/, $(addsuffix _bonus.c, $(SHARED_FILENAMES) \
$(addprefix hud/, hud minimap) \
))
BONUS_OBJ = $(BONUS_SRC:%.c=%.o)

# ----- Compilation Flags ------------------------------------------------------

CFLAGS = -Wall -Werror -Wextra# -O2

SET_OS = $(shell uname)
ifeq ($(SET_OS), Darwin)
	OSLINK = -framework OpenGL -framework AppKit
	DEF_OS = -DBUILD_OS=1
	LINK += -Llib/MLXGE -lmlx -lm
else ifeq ($(SET_OS), Linux)
	INC += -I/usr/include
	LINK += -L/usr/lib
	OSLINK = -lXext -lX11 -lm -lz
	DEF_OS += -DBUILD_OS=2
endif
BUILD_OS = SET_OS=$(SET_OS) CWD=$(shell pwd)

DEBUG =
ifeq ($(DEBUG),1)
	CFLAGS += -g# -fsanitize=address
endif

# ----- Build Targets ----------------------------------------------------------

# 	all - Defaults to mandatory build.
all: $(NAME)
#	m - Builds the mandatory section.
mandatory: $(NAME)
# 	b - Builds the bonus section
bonus: $(NAME_BONUS)

# ----- Compile Source ---------------------------------------------------------

$(CUB3D_OBJ): %.o: %.c
	cc $(CFLAGS) $(DEF_OS) $(INC) -o $@ -c $<

$(MANDATORY_OBJ): %.o: %.c
	cc $(CFLAGS) $(DEF_OS) $(INC) -o $@ -c $<

$(BONUS_OBJ): %.o: %.c
	cc $(CFLAGS) $(DEF_OS) $(INC) -o $@ -c $<

# ----- Compile Executables ----------------------------------------------------

$(NAME): $(MLXGE) $(CUB3D_OBJ) $(MANDATORY_OBJ)
	cc $(CFLAGS) -o $(NAME) $(CUB3D_OBJ) $(MANDATORY_OBJ) $(DEF_OS) $(INC) $(LINK) $(OSLINK)

$(NAME_BONUS): $(MLXGE) $(CUB3D_OBJ) $(BONUS_OBJ)
	cc $(CFLAGS) -o $(NAME_BONUS) $(CUB3D_OBJ) $(BONUS_OBJ) $(DEF_OS) $(INC) $(LINK) $(OSLINK)

# ----- Build Dependencies -----------------------------------------------------

$(MLXGE):
ifeq ($(DEBUG), 1)
	make -C lib/MLXGE $(BUILD_OS) DEBUG=1
else
	make -C lib/MLXGE $(BUILD_OS)
endif

# ----- Clean Targets ----------------------------------------------------------

clean:
	rm -rf $(NAME) $(NAME_BONUS) $(CUB3D_OBJ) $(MANDATORY_OBJ) $(BONUS_OBJ) *.dSYM *.dylib

fclean: clean
	make -C lib/MLXGE fclean

# ----- Rebuild Mandatory Target -----------------------------------------------

re: fclean all

# ----- Norminette Recipe ------------------------------------------------------

norm:
	norminette src
	make -C lib/MLXGE norm

# ------------------------------------------------------------------------------
