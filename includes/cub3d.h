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
# define J 38
# define RIGHT 124
# define LEFT 123
# define UP 126
# define DOWN 125
# define ESC 53
# define WHEELUP 5
# define WHEELDOWN 4
# define WHEELCLICK 3
# define RIGHTCLICK 2
# define LEFTCLICK 2
# define GREEN 65280
# define LIGHT_ORANGE 16764672
# define GREY 10855845
# define CYAN 55024
# define DARK_RED 10884887
# define BRUN 9788928
# define NB_INFOS 8
# define TEXTWIDTH 64
# define TEXTHEIGHT 64
# define MSP 0.08
# define TURNSPEED 0.08
# define PCT 0.16
# define BMP_HEADER 14
# define DIB_HEADER 40
# define PATH_SCREEN_SAVE "../screenshots/save.bmp"

/*
**	informations for
**	the screenshot
*/

typedef struct		s_prtsc
{
	int				filesize;
	int				w;
	int				p_size;
	unsigned short	r;
	unsigned short	g;
	unsigned short	b;
	unsigned char	tab_bmp[BMP_HEADER];
	unsigned char	tab_dip[DIB_HEADER];
	unsigned char	tab_pad[3];

}					t_prtsc;

/*
**	Simple struct for
**	get the sprites pos
*/

typedef struct		s_csprt
{
	float 			x;
	float 			y;
}					t_csprt;

/*
**	All of the informations
**	about the map
*/

typedef struct		s_map
{
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*sprite;
	char			**m;
	int				floor;
	int				ceil;	
	int				m_w;
	int				m_h;
	char			start;
	double			pos_x;
	double			pos_y;
	double			dx;
	double			dy;
	double			px;
	double			py;
	int				nb_sprites;
}					t_map;

/*
**	All of the tools
**	for sprites
*/

typedef struct		s_sprt
{
	t_csprt			*asprt;
	double			*zbuffer;
	int				*sprite_order;
	double			*sprite_distance;
	double 			sprite_x;
	double 			sprite_y;
	double			inv_det;
	double			trsfm_x;
	double			trsfm_y;
	int				screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				v_move_screen;
	int				stripe;
	int				tx;
	int				ty;
	int				color;
}					t_sprt;

/*
**	All of the tools
**	for walls and textures
*/

typedef struct		s_calc
{
	int				x;
	double			camera_x;
	double			rdx;
	double			rdy;
	int				map_x;
	int				map_y;
	double			sdx;
    double			sdy;
	double			dlt_dx;
    double			dlt_dy;
    double			pwd;
	int				stepx;
    int				stepy;
	int				hit;
	int				side;
	int				lineHeight;
	int				drawStart;
	int				drawEnd;
	int				textWidth;
	int				textHeight;
	int				text_num;
	double			wallX;
	int				texX;
	double			step;
	double			textPos;
	int				texY;
	int				color;
}					t_calc;

/*
**	Main sctucture
**	informations about the window
**	screen, img, textures
*/

typedef struct		s_cub
{
	char			save;
	void			*mlx_ptr;
	void			*win_ptr;
	int				win_width;
	int				win_height;
	char			*t;
	void			*img_ptr;
	int				*pix;
	void			*wall_n;
	void			*wall_s;
	void			*wall_e;
	void			*wall_w;
	void			*sprite1;
	int				*addr_sprite;
	int 			*tab_text[4];
	int				side_text;
	int				textures;
	t_calc			clc;
	t_map			*m;
	t_sprt			sprt;
	int				bords;
	int				mpx;
	int				mpy;

}					t_cub;

int					ft_map(t_map *map, t_cub *c, char *ac_map);
int					ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);
int     			check_args(int argc, char **argv, t_cub *c);
char				**ft_split(char *s, char c);
int					ft_atoi(char *nptr);
int					ft_errors(int err, t_cub *c, int ret);
int					f_i(char **str, int ret);
int					ft_free(char **str, int ret, int fd);
void				ft_init(t_cub *c, t_map *map);
void				init_nsew(t_map *map, int i, int j);
int					ft_tablen(char **str, int j);
char				*ft_strdup(char *s1);
int					parse_map(int fd, t_map *map);
int					draw_map(t_cub *c);
void				free_struct(t_map *map);
int					ft_key_event(int key, t_cub *s);
int					ft_exit_button(t_cub *c);
int					ft_exit(t_cub *c, int ret);
void				clc_side_dest(t_cub *c);
void				clc_dist_hit(t_cub *c);
void				clc_start_end(t_cub *c);
void				clc_text(t_cub *c);
void				set_inf_map(t_cub *c, int x);
void				draw_ceil_floor(t_cub *c);
void				move_vert(int key, t_cub *s);
void				move_side(int key, t_cub *s);
void				move_turn(int key, t_cub *s);
int					ft_get_sprites(t_map *m, t_cub *c);
void				draw_sprites(t_cub *c);
void				clc_sprites(t_cub *c);
int					ft_bmp(t_cub *c);
void				find_side(t_cub *c, int id);
#endif