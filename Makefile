SRCS	= src/cub3d.c src/utils/stop.c src/graphics/window_handler.c \
			src/graphics/image_handler.c src/inputs/hooks.c \
			src/inputs/direction.c src/graphics/render.c src/inputs/position_handler.c \
			src/inputs/pov_handler.c src/graphics/draw.c  src/inputs/position.c \
			src/inputs/mouse.c src/raycasting/raycasting.c \
			src/parser/parsing.c src/parser/check_define.c src/utils/str.c \
			src/utils/free.c

# add GL_SILENCE_DEPRECATION to silence mac OpenGL warnings
FLAGS = -Wall -Wextra -Werror -g -DGL_SILENCE_DEPRECATION
CC    = cc
RM    = rm -f
OBJ_DIR = dot_o
OBJS = $(SRCS:%.c=$(OBJ_DIR)/%.o)

NAME	= cub3d

# point to your mlx folders explicitl
MLX_LINUX_DIR = ./src/libraries/minilibx-linux
MLX_MAC_DIR   = ./src/libraries/minilibx_mms_20200219

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@${CC} ${FLAGS} -c $< -o $@

${NAME}: 	${OBJS}
	@make -C ./src/libraries/libft
	@make -C ${MLX_LINUX_DIR}
	@${CC} ${OBJS} -L${MLX_LINUX_DIR} -lmlx -L/usr/lib -I${MLX_LINUX_DIR} -lXext -lX11 -lm -lz -L./src/libraries/libft -lft -o ${NAME} 

# mac: 	${OBJS}
# 	@make -C ./src/libraries/libft
# 	@make -C ${MLX_MAC_DIR}
# 	${CC} ${OBJS} -L${MLX_MAC_DIR} -lmlx -I${MLX_MAC_DIR} -framework OpenGL -framework AppKit -lm -lz -L./src/libraries/libft -lft -o ${NAME} 
# # link against the built mlx in MLX_MAC_DIR and macOS frameworks

all: 		${NAME}

clean:	
	@make fclean -C ./src/libraries/libft
	@make clean -C ${MLX_LINUX_DIR}
	${RM} -r ${OBJ_DIR}
# @make clean -C ${MLX_MAC_DIR}

fclean:		clean
	${RM} ${NAME} 

re:			fclean all

bonus: re
    
.PHONY:		all bonus clean fclean re