gcc -Wall -Wextra -Werror -I minilibx_opengl -framework OpenGl -framework Appkit -L ../minilibx_opengl -lmlx *.c gnl/*.c ../lib/libftprintf.a parsing/*.c utils/*.c -o Cub3D -I ../includes