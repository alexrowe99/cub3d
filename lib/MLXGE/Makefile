NAME = libmlxge.a

LIBALL_DIR = libftall
EXTERN_LIBS = lib/$(LIBALL_DIR)/libftall.a

CORE_DIR = core
CORE_C_SRC = $(addprefix $(CORE_DIR)/, $(addsuffix .c, \
 log core \
 $(addprefix events/, events event_layers hooks key_event) \
 $(addprefix input/, key_input keycodes ) \
 $(addprefix image/, image_quad output_ppm) \
 $(addprefix layers/, layers) \
 $(addprefix render/, draw pixels) \
 $(addprefix window/, window update viewport) \
 $(addprefix math/, vector dimensions) \
))

SET_OS ?= $(shell uname)
ifeq ($(SET_OS), Darwin)
	BUILD_OS = -DBUILD_OS=1
	KEYCODE_FILENAME = macos_keycodes.h
	MLX_BUILD_DIR = mlx/mac
	EXTERN_LIBS += lib/$(MLX_BUILD_DIR)/libmlx.dylib
	CORE_C_SRC += $(addprefix $(CORE_DIR)/render/render_, $(addsuffix .c, mac ))
else ifeq ($(SET_OS), Linux)
	BUILD_OS = -DBUILD_OS=2
	KEYCODE_FILENAME = linux_keycodes.h
	MLX_BUILD_DIR = mlx/linux
	EXTERN_LIBS += lib/$(MLX_BUILD_DIR)/libmlx.a
	CORE_C_SRC += $(addprefix $(CORE_DIR)/render/render_, $(addsuffix .c, linux ))
else
	@echo Your operating system is not supported!
	exit 1
endif

BUILD_OS += -DFULL_PATH_MLXGE='"$(shell pwd)"' -DMLX_KEYCODE_FILE='"$(KEYCODE_FILENAME)"'

CORE_C_OBJS = $(CORE_C_SRC:.c=.o)
MLXGE_OBJS = $(CORE_C_OBJS)

CC = cc -Wall -Werror -Wextra -O2

CWD = 
DEBUG =
MODE = SET_OS=$(SET_OS)
ifeq ($(DEBUG), 1)
	CC += -g# -fsanitize=address
	MODE += DEBUG=1
endif

all: $(NAME)

$(NAME): shared_lib $(MLXGE_OBJS)
	ar rcsv $@ $(MLXGE_OBJS)

ifeq ($(SET_OS), Darwin)
shared_lib: $(EXTERN_LIBS)
	mkdir lib/shared
	cd lib/shared; \
	ar -x ../$(LIBALL_DIR)/libftall.a; \
	ar -rcsv $(NAME) *.o; \
	mv $(NAME) ../../.
else
shared_lib: $(EXTERN_LIBS)
	mkdir lib/shared
	cd lib/shared; \
	ar -x ../$(LIBALL_DIR)/libftall.a; \
	ar -x ../$(MLX_BUILD_DIR)/libmlx.a; \
	ar -rcsv $(NAME) *.o; \
	mv $(NAME) ../../.
endif

$(EXTERN_LIBS):
	@echo "\nBUILDING MAKE IN DIR: lib/$(LIBALL_DIR)"
	make -C lib/$(LIBALL_DIR) $(MODE)
	@echo "\nBUILDING MAKE IN DIR: lib/$(MLX_BUILD_DIR)"
	make -C lib/$(MLX_BUILD_DIR) $(MODE)
ifeq ($(SET_OS), Darwin)
	mv lib/$(MLX_BUILD_DIR)/libmlx.dylib .
	cp libmlx.dylib $(CWD)
else
	
endif

$(CORE_C_OBJS): %.o: %.c
	$(CC) -c $< -I$(CORE_DIR) $(BUILD_OS) -o $@

clean:
	@echo lib/$(MLX_BUILD_DIR) lib/$(LIBALL_DIR)
	rm -rf **/*.o **/**/*.o $(NAME) *.dylib

fclean: clean
	rm -rf lib/shared
	make -C lib/$(MLX_BUILD_DIR) clean
	make -C lib/$(LIBALL_DIR) fclean

re: fclean all

norm:
	norminette *.h core lib/libftall/**/*.[ch]
