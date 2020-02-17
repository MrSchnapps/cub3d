#include "cub3d.h"

int	ft_move(int key, t_cub *s)
{
	double oldDirX;
	double oldPlaneX;

	if (key == W)
	{
		if(s->m->m[(int)(s->m->pos_y + s->m->dx * MOVESPEED + (s->m->dx < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1') 
			s->m->pos_y += s->m->dx * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x + s->m->dy * MOVESPEED + (s->m->dy < 0 ? -W_PROTECT : W_PROTECT))] != '1') 
		  	s->m->pos_x += s->m->dy * MOVESPEED;
	}
	else if (key == S)
	{
		if(s->m->m[(int)(s->m->pos_y - s->m->dx * MOVESPEED - (s->m->dx < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1') 
			s->m->pos_y -= s->m->dx * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x - s->m->dy * MOVESPEED - (s->m->dy < 0 ? -W_PROTECT : W_PROTECT))] != '1')
		  	s->m->pos_x -= s->m->dy * MOVESPEED;
	}
	else if (key == D)
	{
		if(s->m->m[(int)(s->m->pos_y + s->m->dx * MOVESPEED + (s->m->dy < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1') 
			s->m->pos_y += s->m->dy * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x - s->m->dy * MOVESPEED - (s->m->dx < 0 ? -W_PROTECT : W_PROTECT))] != '1') 
		  	s->m->pos_x -= s->m->dx * MOVESPEED;
	}
	else if (key == A)
	{
		if(s->m->m[(int)(s->m->pos_y - s->m->dx * MOVESPEED - (s->m->dy < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1') 
			s->m->pos_y -= s->m->dy * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x + s->m->dy * MOVESPEED + (s->m->dx < 0 ? -W_PROTECT : W_PROTECT))] != '1') 
		  	s->m->pos_x += s->m->dx * MOVESPEED;
	}
	else if (key == DROITE)
    {
      oldDirX = s->m->dx;
      s->m->dx = s->m->dx * cosf(-MOVESPEED) - s->m->dy * sinf(-MOVESPEED);
      s->m->dy = oldDirX * sinf(-MOVESPEED) + s->m->dy * cosf(-MOVESPEED);
      oldPlaneX = s->m->px;
      s->m->px = s->m->px * cosf(-MOVESPEED) - s->m->py * sinf(-MOVESPEED);
      s->m->py = oldPlaneX * sinf(-MOVESPEED) + s->m->py * cosf(-MOVESPEED);
    }
	else if (key == GAUCHE)
    {
      oldDirX = s->m->dx;
      s->m->dx = s->m->dx * cosf(MOVESPEED) - s->m->dy * sinf(MOVESPEED);
      s->m->dy = oldDirX * sinf(MOVESPEED) + s->m->dy * cosf(MOVESPEED);
      oldPlaneX = s->m->px;
      s->m->px = s->m->px * cosf(MOVESPEED) - s->m->py * sinf(MOVESPEED);
      s->m->py = oldPlaneX * sinf(MOVESPEED) + s->m->py * cosf(MOVESPEED);
    }
	//mlx_destroy_window (s->mlx_ptr, s->img_ptr);
	if (s->textures == 1)
		draw_text_map(s);
	else
		draw_map(s);
	return (1);
}