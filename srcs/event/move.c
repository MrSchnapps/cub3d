#include "cub3d.h"

void	clc_move(int key, t_cub *s, int *y, int *x)
{
	if (key == W)
	{
		*y = (int)(s->m->pos_y + s->m->dx * MSP + (s->m->dx < 0 ? -PCT : PCT));
		*x = (int)(s->m->pos_x + s->m->dy * MSP + (s->m->dy < 0 ? -PCT : PCT));
	}
	else if (key == S)
	{
		*y = (int)(s->m->pos_y - s->m->dx * MSP - (s->m->dx < 0 ? -PCT : PCT));
		*x = (int)(s->m->pos_x - s->m->dy * MSP - (s->m->dy < 0 ? -PCT : PCT));
	}
	else if (key == D)
	{
		*y = (int)(s->m->pos_y + s->m->dx * MSP + (s->m->dy < 0 ? -PCT : PCT));

		*x = (int)(s->m->pos_x - s->m->dy * MSP - (s->m->dx < 0 ? -PCT : PCT));
	}
	else if (key == A)
	{
		*y = (int)(s->m->pos_y - s->m->dx * MSP - (s->m->dy < 0 ? -PCT : PCT));

		*x = (int)(s->m->pos_x + s->m->dy * MSP + (s->m->dx < 0 ? -PCT : PCT));
	}
}

void	move_vert(int key, t_cub *s)
{
	int y;
	int x;

	clc_move(key, s, &y, &x);
	if (key == W)
	{
		if(s->m->m[y][(int)s->m->pos_x] < '1' ||
			s->m->m[y][(int)s->m->pos_x] > '2')
			s->m->pos_y += s->m->dx * MSP;
      	if(s->m->m[(int)s->m->pos_y][x] < '1' ||
		  	s->m->m[(int)s->m->pos_y][x] > '2')
		  	s->m->pos_x += s->m->dy * MSP;
	}
	else if (key == S)
	{
		if(s->m->m[y][(int)s->m->pos_x] < '1' ||
			s->m->m[y][(int)s->m->pos_x] > '2')
			s->m->pos_y -= s->m->dx * MSP;
      	if(s->m->m[(int)s->m->pos_y][x] < '1' ||
		  	s->m->m[(int)s->m->pos_y][x] > '2')
		  	s->m->pos_x -= s->m->dy * MSP;
	}
	draw_map(s);
}

void	move_side(int key, t_cub *s)
{
	int y;
	int x;

	clc_move(key, s, &y, &x);
	if (key == D)
	{
		if(s->m->m[y][(int)s->m->pos_x] < '1' || s->m->m[y][(int)s->m->pos_x] > '2')
			s->m->pos_y += s->m->dy * MSP;
      	if(s->m->m[(int)s->m->pos_y][x] < '1' || s->m->m[(int)s->m->pos_y][x] > '2')
		  	s->m->pos_x -= s->m->dx * MSP;
	}
	else if (key == A)
	{
		if(s->m->m[y][(int)s->m->pos_x] < '1' || s->m->m[y][(int)s->m->pos_x] > '2')
			s->m->pos_y -= s->m->dy * MSP;
      	if(s->m->m[(int)s->m->pos_y][x] < '1' || s->m->m[(int)s->m->pos_y][x] > '2') 
		  	s->m->pos_x += s->m->dx * MSP;
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
