NAME=libmlxge.a

CORE_DIR=core
CORE_C_SRC=$(addprefix $(CORE_DIR)/, $(addsuffix .c, \
 log vector dimensions core window layers events frame key_input render \
))

SET_OS=
ifeq ($(strip $(SET_OS)),)
	SET_OS=$(shell uname)
	ifeq ($(SET_OS), Darwin)
		SET_OS=1
	else ifeq ($(SET_OS), Linux)
		SET_OS_OS=2
	else
		@echo Your operating system is not supported!
		exit 1
	endif
endif
ifeq ($(SET_OS), 1)
	BUILD_OS=-DBUILD_OS=1
	MLX_BUILD_DIR=mlx/macos
else ifeq ($(SET_OS), 2)
	BUILD_OS=-DBUILD_OS=2
	MLX_BUILD_DIR=mlx/linux
endif

LIBALL_DIR=libftall
EXTERN_LIBS=lib/$(MLX_BUILD_DIR)/libmlx.a lib/$(LIBALL_DIR)/libftall.a

CORE_C_OBJS=$(CORE_C_SRC:.c=.o)
MLXGE_OBJS=$(CORE_C_OBJS)

CC=cc -Wall -Werror -Wextra

DEBUG=
MODE=
ifeq ($(DEBUG), 1)
	CC=cc -Wall -Werror -Wextra -g -fsanitize=address
	MODE=DEBUG=1
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
	make -C lib/$(LIBALL_DIR) $(MODE)
# cp -rf lib/$(LIBALL_DIR)/libftall.h core/.
	make -C lib/$(MLX_BUILD_DIR) $(MODE)
# cp -rf lib/$(MLX_BUILD_DIR)/mlx.h core/.

$(CORE_C_OBJS): %.o: %.c
	$(CC) -c $< -I$(CORE_DIR) $(BUILD_OS) -o $@

clean:
	rm -rf **/*.o $(NAME)
# rm -rf core/mlx.h core/libftall.h

fclean: clean
	rm -rf lib/shared
	make -C lib/$(MLX_BUILD_DIR) clean
	make -C lib/$(LIBALL_DIR) fclean

re: fclean all
