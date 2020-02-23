#include "cub3d.h"

void	move_vert(int key, t_cub *s)
{
	if (key == W)
	{
		if(s->m->m[(int)(s->m->pos_y + s->m->dx * MOVESPEED + 
			(s->m->dx < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1') 
			s->m->pos_y += s->m->dx * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x + s->m->dy * MOVESPEED + 
		  	(s->m->dy < 0 ? -W_PROTECT : W_PROTECT))] != '1') 
		  	s->m->pos_x += s->m->dy * MOVESPEED;
	}
	else if (key == S)
	{
		if(s->m->m[(int)(s->m->pos_y - s->m->dx * MOVESPEED - 
			(s->m->dx < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1') 
			s->m->pos_y -= s->m->dx * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x - s->m->dy * MOVESPEED - 
		  	(s->m->dy < 0 ? -W_PROTECT : W_PROTECT))] != '1')
		  	s->m->pos_x -= s->m->dy * MOVESPEED;
	}
	draw_map(s);
}

void	move_side(int key, t_cub *s)
{
	if (key == D)
	{
		if(s->m->m[(int)(s->m->pos_y + s->m->dx * MOVESPEED + 
			(s->m->dy < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1') 
			s->m->pos_y += s->m->dy * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x - s->m->dy * MOVESPEED -
		  	(s->m->dx < 0 ? -W_PROTECT : W_PROTECT))] != '1') 
		  	s->m->pos_x -= s->m->dx * MOVESPEED;
	}
	else if (key == A)
	{
		if(s->m->m[(int)(s->m->pos_y - s->m->dx * MOVESPEED - 
			(s->m->dy < 0 ? -W_PROTECT : W_PROTECT))][(int)s->m->pos_x] != '1')
			s->m->pos_y -= s->m->dy * MOVESPEED;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x + s->m->dy * MOVESPEED + 
		  	(s->m->dx < 0 ? -W_PROTECT : W_PROTECT))] != '1') 
		  	s->m->pos_x += s->m->dx * MOVESPEED;
	}
	draw_map(s);
}

void	move_turn(int key, t_cub *s)
{
	double oldDirX;
	double oldPlaneX;

	if (key == RIGHT)
    {
      oldDirX = s->m->dx;
      s->m->dx = s->m->dx * cosf(-TURNSPEED) - s->m->dy * sinf(-TURNSPEED);
      s->m->dy = oldDirX * sinf(-TURNSPEED) + s->m->dy * cosf(-TURNSPEED);
      oldPlaneX = s->m->px;
      s->m->px = s->m->px * cosf(-TURNSPEED) - s->m->py * sinf(-TURNSPEED);
      s->m->py = oldPlaneX * sinf(-TURNSPEED) + s->m->py * cosf(-TURNSPEED);
    }
	else if (key == LEFT)
    {
      oldDirX = s->m->dx;
      s->m->dx = s->m->dx * cosf(TURNSPEED) - s->m->dy * sinf(TURNSPEED);
      s->m->dy = oldDirX * sinf(TURNSPEED) + s->m->dy * cosf(TURNSPEED);
      oldPlaneX = s->m->px;
      s->m->px = s->m->px * cosf(TURNSPEED) - s->m->py * sinf(TURNSPEED);
      s->m->py = oldPlaneX * sinf(TURNSPEED) + s->m->py * cosf(TURNSPEED);
    }
	draw_map(s);
}
