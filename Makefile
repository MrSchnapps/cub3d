NAME = Cub3D

SRCS = srcs/draw/*.c \
		srcs/event/*.c \
		srcs/gnl/*.c \
		srcs/parsing/*.c \
		srcs/utils/*.c \
		srcs/main.c

HEADER = includes

OBJS = ${SRCS:.c=.o}
CC = gcc
CFLAGS = -Wall -Wextra -Werror

MLXFLAGS = -I minilibx_opengl -framework OpenGl -framework Appkit -L ../minilibx_opengl -lmlx

LIBPRINTF = lib/libftprintf.a

all:		$(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(MLXFLAGS) -I $(HEADER) $(LIBPRINTF)

$(NAME): $(OBJ)
	$(CC) -o $@ $(OBJ) $(LDFLAGS)

.c.o:
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -rf */*/*.o

fclean:
	clean
	${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re