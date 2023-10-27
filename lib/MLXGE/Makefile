NAME = libmlxge.a

CORE_DIR = core
CORE_C_SRC = $(addprefix $(CORE_DIR)/, $(addsuffix .c, \
 $(addprefix events/, events event_layers hooks key_event) \
 log core window layers update viewport image_quad draw output_ppm \
))

SET_OS ?= $(shell uname)
ifeq ($(SET_OS), Darwin)
	BUILD_OS = -DBUILD_OS=1
	MLX_BUILD_DIR = mlx/mac
	CORE_C_SRC += $(addprefix $(CORE_DIR)/render_, $(addsuffix .c, mac ))
else ifeq ($(SET_OS), Linux)
	BUILD_OS = -DBUILD_OS=2
	MLX_BUILD_DIR = mlx/linux
	CORE_C_SRC += $(addprefix $(CORE_DIR)/render_, $(addsuffix .c, linux ))
else
	@echo Your operating system is not supported!
	exit 1
endif

LIBALL_DIR = libftall
EXTERN_LIBS = lib/$(MLX_BUILD_DIR)/libmlx.a lib/$(LIBALL_DIR)/libftall.a

CORE_C_OBJS = $(CORE_C_SRC:.c=.o)
MLXGE_OBJS = $(CORE_C_OBJS)

CC=cc -Wall -Werror -Wextra #-O2

DEBUG =
MODE = SET_OS=$(SET_OS)
ifeq ($(DEBUG), 1)
	CC += -g #-fsanitize=address
	MODE += DEBUG=1
endif

all: $(NAME)

$(NAME): shared_lib $(MLXGE_OBJS)
	ar rcsv $@ $(MLXGE_OBJS)

shared_lib: $(EXTERN_LIBS)
	mkdir lib/shared
	cd lib/shared; \
	ar -x ../$(MLX_BUILD_DIR)/libmlx.a; \
	ar -x ../$(LIBALL_DIR)/libftall.a; \
	ar -rcsv $(NAME) *.o; \
	mv $(NAME) ../../.; \

$(EXTERN_LIBS):
	@echo "\nBUILDING MAKE IN DIR: lib/$(LIBALL_DIR)"
	make -C lib/$(LIBALL_DIR) $(MODE)
	@echo "\nBUILDING MAKE IN DIR: lib/$(MLX_BUILD_DIR)"
	make -C lib/$(MLX_BUILD_DIR) $(MODE)

$(CORE_C_OBJS): %.o: %.c
	$(CC) -c $< -I$(CORE_DIR) $(BUILD_OS) -o $@

clean:
	@echo lib/$(MLX_BUILD_DIR) lib/$(LIBALL_DIR)
	rm -rf **/*.o **/**/*.o $(NAME)

fclean: clean
	rm -rf lib/shared
	make -C lib/$(MLX_BUILD_DIR) clean
	make -C lib/$(LIBALL_DIR) fclean

re: fclean all

norm:
	norminette *.h core lib/libftall/**/*.[ch]
