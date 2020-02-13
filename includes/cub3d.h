#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>
# include "../minilibx_opengl/mlx.h"
# include "get_next_line.h"
# include "ft_printf.h"
# include <math.h>

# define KPRESS 2
# define KCLICK	3
# define MCLICK	4
# define MPRESS 5
# define MMOVE 	6
# define W 13
# define S 1
# define A 0
# define D 2
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
# define ORANGE_CLAIR 16764672
# define GRIS 10855845
# define MARRON 13143808
# define CYAN 55024
# define POURPRE 10884887
# define BRUN 9788928
# define J 38
# define NB_INFOS 8

typedef struct	s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sprite;
	int			floor;
	int			ceil;
	char		**m;
	int			m_w;
	int			m_h;
	char		start;
	double		pos_x;
	double		pos_y;
	double		dx;
	double		dy;
	double		px;
	double		py;
}				t_map;

typedef struct s_calc
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	sideDistX;
    double	sideDistY;
	double	deltaDistX;
    double	deltaDistY;
    double	perpWallDist;
	int		stepX;
    int		stepY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	int		done;
	int		textWidth;
	int		textHeight;
}				t_calc;

typedef struct	s_cub
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
	char	*t;
	void	*img_ptr;
	void	*wall_n;
	void	*wall_s;
	void	*wall_e;
	void	*wall_w;
	void	*sprite1;
	t_calc	clc;
	t_map	*m;
}				t_cub;

int				ft_map(t_map *map, t_cub *c, char *ac_map);
int				ft_strlen(char *str);
int				ft_strcmp(char *s1, char *s2);
int     		check_args(int argc, char **argv);
char			**ft_split(char *s, char c);
int				ft_atoi(char *nptr);
int				ft_errors(int err);
int				f_i(char **str, int ret);
int				ft_free(char **str, int ret, int fd);
void			ft_init_map(t_cub *c, t_map *map);
void			init_nsew(t_map *map, int i, int j);
int				ft_tablen(char **str, int j);
char			*ft_strdup(char *s1);
int				parse_map(int fd, t_map *map);
int				draw_map(t_cub *c);
void			free_struct(t_map *map);
int				ft_key_event(int key, t_cub *s);
int				ft_move(int key, t_cub *s);
int				ft_exit_button(t_cub *s);
int				ft_exit_esc(t_cub *s);
#endif