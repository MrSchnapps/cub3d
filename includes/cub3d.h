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
# define T 17
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
# define TEXTWIDTH 64
# define TEXTHEIGHT 64
# define MOVESPEED 0.08
# define TURNSPEED 0.08
# define W_PROTECT 0.16
# define UDIV 1
# define VDIV 1
# define VMOVE 0.0

/*
**	Simple struct for
**	get the sprites pos
*/

typedef struct	s_csprt
{
	float x;
	float y;
}				t_csprt;

/*
**	All of the informations
**	about the map
*/

typedef struct	s_map
{
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	char		*sprite;
	char		**m;
	int			floor;
	int			ceil;	
	int			m_w;
	int			m_h;
	char		start;
	double		pos_x;
	double		pos_y;
	double		dx;
	double		dy;
	double		px;
	double		py;
	int			nb_sprites;
}				t_map;

/*
**	All of the tools
**	for sprites
*/

typedef struct	s_sprt
{
	t_csprt		*all_sprites;
	double		*zbuffer;
	int			*sprite_order;
	double		*sprite_distance;
	double 		sprite_x;
	double 		sprite_y;
	double		inv_det;
	double		transform_x;
	double		transform_y;
	int			screen_x;
	int			sprite_height;
	int			draw_start_y;
	int			draw_end_y;
	int			sprite_width;
	int			draw_start_x;
	int			draw_end_x;
	int			v_move_screen;
	int			stripe;
	int			s_text_x;
	int			s_text_y;
	int			color;
}				t_sprt;

/*
**	All of the tools
**	for walls and textures
*/

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
	int		textWidth;
	int		textHeight;
	int		text_num;
	double	wallX;
	int		texX;
	double	step;
	double	textPos;
	int		texY;
	int		color;
}				t_calc;

/*
**	Main sctucture
**	informations about the window
**	screen, img, textures
*/

typedef struct	s_cub
{
	char	save;
	void	*mlx_ptr;
	void	*win_ptr;
	int		win_width;
	int		win_height;
	char	*t;
	void	*img_ptr;
	int		*pix;
	void	*wall_n;
	void	*wall_s;
	void	*wall_e;
	void	*wall_w;
	void	*sprite1;
	int		*addr_sprite;
	int 	*tab_text[4];
	int		side_text;
	int		textures;
	t_calc	clc;
	t_map	*m;
	t_sprt	sprt;

	int bords;
	int mpx;
	int mpy;

}				t_cub;

int				ft_map(t_map *map, t_cub *c, char *ac_map);
int				ft_strlen(char *str);
int				ft_strcmp(char *s1, char *s2);
int     		check_args(int argc, char **argv, t_cub *c);
char			**ft_split(char *s, char c);
int				ft_atoi(char *nptr);
int				ft_errors(int err, t_cub *c, int ret);
int				f_i(char **str, int ret);
int				ft_free(char **str, int ret, int fd);
void			ft_init(t_cub *c, t_map *map);
void			init_nsew(t_map *map, int i, int j);
int				ft_tablen(char **str, int j);
char			*ft_strdup(char *s1);
int				parse_map(int fd, t_map *map);
int				draw_map(t_cub *c);
void			free_struct(t_map *map);
int				ft_key_event(int key, t_cub *s);
int				ft_exit_button(t_cub *c);
int				ft_exit(t_cub *c, int ret);
void			clc_side_dest(t_cub *c);
void			clc_dist_hit(t_cub *c);
void			clc_start_end(t_cub *c);
void			clc_text(t_cub *c);
void			set_inf_map(t_cub *c, int x);
void			draw_ceil_floor(t_cub *c);
void			move_vert(int key, t_cub *s);
void			move_side(int key, t_cub *s);
void			move_turn(int key, t_cub *s);
int				ft_get_sprites(t_map *m, t_cub *c);
void			test(t_cub *c);
void			draw_sprites(t_cub *c);
void			clc_sprites(t_cub *c);
#endif