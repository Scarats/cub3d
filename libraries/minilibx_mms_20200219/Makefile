MODULE_SRC= mlx_image.swift mlx_window.swift mlx_init.swift
MODULE_OBJ=$(MODULE_SRC:.swift=.swiftmodule)
MODULE_OBJS=$(MODULE_SRC:.swift=.o)

SRC= interface.swift $(MODULE_SRC)
OBJ=$(SRC:.swift=.o)

C_SRC= mlx_xpm.c mlx_png.c mlx_string_put.c
C_OBJ=$(C_SRC:.c=.o)
CFLAGS=-O3

NAME=libmlx.dylib

INC=-I.
#OPTI=-Ounchecked

SWIFT := $(shell xcrun -sdk macosx --find swiftc)
SWIFT_SDK := $(shell xcrun --sdk macosx --show-sdk-path)
SWIFT_FLAGS := -sdk $(SWIFT_SDK) -F $(SWIFT_SDK)/System/Library/Frameworks

all: $(NAME)

$(NAME): $(MODULE_OBJ) $(OBJ) $(C_OBJ)
	swiftc $(OPTI) $(INC) -o $(NAME) -emit-library $(OBJ) $(C_OBJ) -lz

%.o: %.swift
	$(SWIFT) $(OPTI) $(INC) $(SWIFT_FLAGS) -parse-as-library -emit-module \
		-emit-module-path $(basename $@).swiftmodule \
		-module-name $(basename $@) \
		-module-link-name $(basename $@) \
		-c $< -o $@

%.swiftmodule: %.o
	@:

