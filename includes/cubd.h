#ifndef CUBD_H
# define CUBD_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../minilibx_opengl/mlx.h"

# define KPRESS 2
# define KCLICK	3
# define MCLICK	4
# define MPRESS 5
# define MMOVE 	6
# define DROITE 124
# define GAUCHE 123
# define HAUT 126
# define BAS 125
# define ESC 53
# define WHEELUP 5
# define WHEELDOWN 4
# define WHEELCLICK 3
# define RIGHTCLICK 2
# define LEFTCLICK 2
# define RED 16711680
# define BLUE 255
# define GREEN 65280
# define ORANGE 16753664
# define J 38

typedef struct	s_cubd
{
	void *mlx_ptr;
	void *win_ptr;
	int x;
	int y;
}				t_cubd;

typedef struct	s_map
{
	int 		res_x;
	int 		res_y;
	char *str 	no;
	char *str 	so;
	char *str 	we;
	char *str 	ea;
	char *str 	sprite;
	int			sol;
	int			ciel;	
}				t_map;

int				parse_map(t_map *map);
#endif