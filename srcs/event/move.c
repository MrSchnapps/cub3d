#include "cub3d.h"

int	ft_move(int key, t_cub *s)
{
	double oldDirX;
	double oldPlaneX;

	if (key == W)
	{
		if(s->m->m[(int)(s->m->pos_y + s->m->dx * 0.1)][(int)s->m->pos_x] != '1') 
			s->m->pos_y += s->m->dx * 0.1;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x + s->m->dy * 0.1)] != '1') 
		  	s->m->pos_x += s->m->dy * 0.1;
	}
	if (key == S)
	{
		if(s->m->m[(int)(s->m->pos_y - s->m->dx * 0.1)][(int)s->m->pos_x] != '1') 
			s->m->pos_y -= s->m->dx * 0.1;
      	if(s->m->m[(int)s->m->pos_y][(int)(s->m->pos_x - s->m->dy * 0.1)] != '1')
		  	s->m->pos_x -= s->m->dy * 0.1;
	}
	if (key == D)
    {
      //both camera direction and camera plane must be rotated
      oldDirX = s->m->dx;
      s->m->dx = s->m->dx * cosf(-0.1) - s->m->dy * sinf(-0.1);
      s->m->dy = oldDirX * sinf(-0.1) + s->m->dy * cosf(-0.1);
      oldPlaneX = s->m->px;
      s->m->px = s->m->px * cosf(-0.1) - s->m->py * sinf(-0.1);
      s->m->py = oldPlaneX * sinf(-0.1) + s->m->py * cosf(-0.1);
	  /*printf("\ndx ==> |%f|\n", s->m->dx);
	  printf("\ndy ==> |%f|\n", s->m->dy);
	  printf("\npx ==> |%f|\n", s->m->px);
	  printf("\npy ==> |%f|\n", s->m->py);
	  printf("\n----------------------------------\n");*/
    }
	if (key == A)
    {
      //both camera direction and camera plane must be rotated
      oldDirX = s->m->dx;
      s->m->dx = s->m->dx * cosf(0.1) - s->m->dy * sinf(0.1);
      s->m->dy = oldDirX * sinf(0.1) + s->m->dy * cosf(0.1);
      oldPlaneX = s->m->px;
      s->m->px = s->m->px * cosf(0.1) - s->m->py * sinf(0.1);
      s->m->py = oldPlaneX * sinf(0.1) + s->m->py * cosf(0.1);
    }
	//mlx_destroy_window (s->mlx_ptr, s->img_ptr);
	draw_map(s);
	return (1);
}