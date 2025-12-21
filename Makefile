SRCS	= src/cub3d.c src/utils/stop.c src/graphics/window_handler.c \
			src/graphics/image_handler.c src/inputs/hooks.c \
			src/inputs/direction.c src/graphics/render.c src/inputs/position_handler.c \
			src/inputs/pov_handler.c src/graphics/draw.c  src/inputs/position.c \
			src/inputs/mouse.c src/raycasting/raycasting.c \
			src/parser/parsing.c src/parser/check_define.c \
			src/utils/free.c src/utils/init.c src/graphics/minimap.c \
			src/graphics/texture.c src/parser/save_assets.c src/parser/save_sprites.c \

FLAGS = -Wall -Wextra -Werror -g -DGL_SILENCE_DEPRECATION
CC    = cc
RM    = rm -f
OBJ_DIR = dot_o
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME	= cub3d

MLX_LINUX_DIR = ./libraries/minilibx-linux
MLX_MAC_DIR   = ./libraries/minilibx_mms_20200219

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@

${NAME}: 	${OBJS}
	@make -C ./libraries/libft 
	@make -C ${MLX_LINUX_DIR}
	@${CC} ${OBJS} -L${MLX_LINUX_DIR} -lmlx -L/usr/lib -I${MLX_LINUX_DIR} -lXext -lX11 -lm -lz -L ./libraries/libft -lft -o ${NAME} 2>&1

all: 		${NAME}

clean:
	@make fclean -C ./libraries/libft
	@make clean -C ${MLX_LINUX_DIR}
	@${RM} -r ${OBJ_DIR}

fclean:		clean
	@${RM} ${NAME}

re:			fclean all

bonus: re

.PHONY:		all bonus clean fclean re
