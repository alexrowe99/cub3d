


MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

NAME=libmlx.dylib
STATIC=libmlx.a

INC=-I.
#OPTI=-Ounchecked

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	swiftc $(OPTI) $(INC) $(OBJ) $(C_OBJ) -emit-module -emit-library -o $(NAME) -lz
	swiftc $(OPTI) $(INC) $(OBJ) $(C_OBJ) -emit-module -emit-library -static -o $(STATIC) -lz


%.o: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@

%.swiftmodule: %.swift
	swiftc $(OPTI) $(INC) -parse-as-library -c $< -o $@ -emit-module -module-name $(patsubst %.swift,%,$<) -module-link-name $(patsubst %.swift,%,$<)

clean:
	rm -f $(NAME) $(STATIC) $(OBJ) $(MODULE_OBJ) $(C_OBJ) *.swiftdoc *.swiftsourceinfo *~

