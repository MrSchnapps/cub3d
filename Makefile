NAME = Cub3D
MLX_PATH = ./minilibx_opengl
FPF_PATH = ./ft_fpf
SRCS = srcs/draw/clc_sprites.c \
		srcs/draw/clc_walls.c \
		srcs/draw/ft_bmp.c \
		srcs/draw/ft_draw.c \
		srcs/draw/walls2.c \
		srcs/event/hook.c \
		srcs/event/move.c \
		srcs/gnl/get_next_line.c \
		srcs/gnl/get_next_line_utils.c \
		srcs/parsing/ft_map.c \
		srcs/parsing/ft_parse_map.c \
		srcs/parsing/ft_parse_sprite.c \
		srcs/parsing/init.c \
		srcs/utils/exit.c \
		srcs/utils/ft_errors.c \
		srcs/utils/ft_free.c \
		srcs/utils/ft_split.c \
		srcs/utils/utils.c \
		srcs/main.c
HEADER = includes
OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -I minilibx_opengl -framework OpenGl -framework Appkit -L minilibx_opengl -lmlx
LIBFPF = lib/libfpf.a

all: fpf_all mlx_all $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MLXFLAGS) -I $(HEADER) $(LIBFPF)

.c.o:
	$(CC) $(CFLAGS) -c $< -o $@  -I $(HEADER)

clean:
	rm -rf $(OBJS)

fclean:		clean
			${RM} ${NAME}

re:		fclean all

bonus: all

mlx_all:
	make -C $(MLX_PATH) all

mlx_clean:
	make -C $(MLX_PATH) clean

fpf_all:
	make -C $(FPF_PATH) all

fpf_clean:
	make -C $(FPF_PATH) clean

clean_all: clean mlx_clean fpf_clean

clean_mf: clean fpf_clean

.PHONY: all clean fclean re bonus mlx_all mlx_clean clean_mf fpf_all fpf_clean