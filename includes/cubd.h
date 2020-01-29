#ifndef CUBD_H
# define CUBD_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../minilibx_opengl/mlx.h"
# include "get_next_line.h"
# include "../includes/ft_printf.h"

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
# define NB_INFOS 8

typedef struct	s_cubd
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		x;
	int		y;
}				t_cubd;

typedef struct	s_map
{
	int		res_x;
	int		res_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*sprite;
	int		sol;
	int		ciel;	
}				t_map;

typedef struct s_infos
{
	int r;
	int	no;
	int	so;
	int we;
	int ea;
	int	s;

}
int     		ft_map(t_map *map, char *ac_map);
int				ft_strlen(char *str);
int				ft_strcmp(char *s1, char *s2);
void			ft_putstr_fd(char *s, int fd);
int     		check_args(int argc, char **argv);
char			**ft_split(char const *s, char c);
#endif