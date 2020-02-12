#include "cub3d.h"


int	ft_exit_button(t_cub *s)
{
	printf("on a appuye sur la croix\n");
	mlx_destroy_image(s->mlx_ptr, s->img_ptr);
	mlx_clear_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	exit(0);
	return (1);
}

int	ft_exit_esc(t_cub *s)
{
	printf("on a appuye sur ESC\n");
	mlx_destroy_image(s->mlx_ptr, s->img_ptr);
	mlx_clear_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	exit(0);
	return (1);
}

void	free_struct(t_map *map)
{
	free(map->no);
	free(map->we);
	free(map->ea);
	free(map->so);
	free(map->sprite);
	f_i(map->m, 0);	
}

double	absolute(double nb)
{
	if (nb < 0)
		return (nb * -1);
	return (nb);
}

void vertLine(int x, int drawStart, int drawEnd, t_cub *c, int side)
{
	int	*pix;
	int	id;
	int i;

	i = 0;
	pix = (int *)mlx_get_data_addr(c->img_ptr, &id, &id, &id);
	//printf("\nStart ==> |%d|\nEnd ==> |%d|\n", drawStart, drawEnd);
	while (i < drawStart)
	{
		pix[i * c->win_width + x] = CYAN;
		i++;
	}
	while (drawStart < drawEnd)
	{
		//if (x < c->win_width && drawStart < c->win_height)
		//{	
			if (side == 0)
				pix[drawStart * c->win_width + x] = GRIS;
			else
				pix[drawStart * c->win_width + x] = ORANGE_CLAIR;
			//drawStart += c->win_width;
			drawStart++;
		//}
	}
	while (drawEnd < c->win_height)
	{
		pix[drawEnd * c->win_width + x] = MARRON;
		drawEnd++;
	}
	
}

int		draw_map(t_cub *c)
{
	int		x;
	/*double	camera_x;
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
	int		done;*/

	if (!(c->img_ptr = mlx_new_image(c->mlx_ptr, c->win_width, c->win_height)))
		exit(1);
	c->clc.done = 1;
	x = -1;
	while (++x < c->win_width)
	{
		c->clc.camera_x = 2 * x / (double)c->win_width - 1;
		c->clc.ray_dir_x = c->m->dx + c->m->px * c->clc.camera_x;
		c->clc.ray_dir_y = c->m->dy + c->m->py * c->clc.camera_x;

		c->clc.map_x = (int)c->m->s_y;
		c->clc.map_y = (int)c->m->s_x;

		c->clc.deltaDistX = fabs(1 / c->clc.ray_dir_x);
		c->clc.deltaDistY = fabs(1 / c->clc.ray_dir_y);
		//deltaDistX = (ray_dir_x == 0) ? 0 : ((ray_dir_x == 0) ? 1 : fabs(1 / ray_dir_x));
     	//deltaDistY = (ray_dir_y == 0) ? 0 : ((ray_dir_y == 0) ? 1 : fabs(1 / ray_dir_y));
		c->clc.hit = 0;
		if (c->clc.ray_dir_x < 0)
		{
			c->clc.stepX = -1;
			c->clc.sideDistX = (c->m->s_y - c->clc.map_x) * c->clc.deltaDistX;
		}
		else
		{
			c->clc.stepX = 1;
			c->clc.sideDistX = (c->clc.map_x + 1.0 - c->m->s_y) * c->clc.deltaDistX;
		}
		if (c->clc.ray_dir_y < 0)
		{
			c->clc.stepY = -1;
			c->clc.sideDistY = (c->m->s_x - c->clc.map_y) * c->clc.deltaDistY;
		}
		else
		{
			c->clc.stepY = 1;
			c->clc.sideDistY = (c->clc.map_y + 1.0 - c->m->s_x) * c->clc.deltaDistY;
		}
		while (c->clc.hit == 0)
		{
			if (c->clc.sideDistX < c->clc.sideDistY)
			{
				c->clc.sideDistX += c->clc.deltaDistX;
				c->clc.map_x += c->clc.stepX;
				c->clc.side = 0;
			}
			else
			{
				c->clc.sideDistY += c->clc.deltaDistY;
				c->clc.map_y += c->clc.stepY;
				c->clc.side = 1;
			}
			if (c->m->m[c->clc.map_x][c->clc.map_y] == '1') 
				c->clc.hit = 1;
		}
		/*printf("\nmap->x |%d|\n", map_x);
		printf("\nmap->y |%d|\n", map_y);*/
		if (c->clc.side == 0)
			c->clc.perpWallDist = (c->clc.map_x - c->m->s_y + (1 - c->clc.stepX) / 2) / c->clc.ray_dir_x;
		else
			c->clc.perpWallDist = (c->clc.map_y - c->m->s_x + (1 - c->clc.stepY) / 2) / c->clc.ray_dir_y;

		//printf("pero ==> |%f|\n", perpWallDist);
		c->clc.lineHeight = (int)(c->win_height / c->clc.perpWallDist);
		c->clc.drawStart =  (c->win_height / 2) - (c->clc.lineHeight / 2);
		if (c->clc.drawStart < 0)
			c->clc.drawStart = 0;
		c->clc.drawEnd = (c->clc.lineHeight / 2) + (c->win_height / 2);
		if (c->clc.drawEnd >= c->win_height)
			c->clc.drawEnd = c->win_height - 1;
		vertLine(x, c->clc.drawStart, c->clc.drawEnd, c, c->clc.side);
	}
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	return (0);
}

int	ft_dep(int a, t_cub *s)
{
	double oldDirX;
	double oldPlaneX;

	if (a == W)
	{
		if(s->m->m[(int)(s->m->s_y + s->m->dx * 0.1)][(int)s->m->s_x] == '0') 
			s->m->s_y += s->m->dx * 0.1;
      	if(s->m->m[(int)s->m->s_y][(int)(s->m->s_x + s->m->dy * 0.1)] == '0') 
		  	s->m->s_x += s->m->dy * 0.1;
	}
	if (a == S)
	{
		if(s->m->m[(int)(s->m->s_y - s->m->dx * 0.1)][(int)s->m->s_x] == '0') 
			s->m->s_y -= s->m->dx * 0.1;
      	if(s->m->m[(int)s->m->s_y][(int)(s->m->s_x - s->m->dy * 0.1)] == '0') 
		  	s->m->s_x -= s->m->dy * 0.1;
	}
	if (a == D)
    {
      //both camera direction and camera plane must be rotated
      oldDirX = s->m->dx;
      s->m->dx = s->m->dx * cosf(-0.1) - s->m->dy * sinf(-0.1);
      s->m->dy = oldDirX * sinf(-0.1) + s->m->dy * cosf(-0.1);
      oldPlaneX = s->m->px;
      s->m->px = s->m->px * cosf(-0.1) - s->m->py * sinf(-0.1);
      s->m->py = oldPlaneX * sinf(-0.1) + s->m->py * cosf(-0.1);
	  printf("\ndx ==> |%f|\n", s->m->dx);
	  printf("\ndy ==> |%f|\n", s->m->dy);
	  printf("\npx ==> |%f|\n", s->m->px);
	  printf("\npy ==> |%f|\n", s->m->py);
	  printf("\n----------------------------------\n");
    }
	if (a == A)
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

int ft_key_event(int a, t_cub *s)
{
	if (a == ESC)
		ft_exit_esc(s);
	/*if ((a >= 123 && a <= 126) || a == 0)
		ft_draw(s, a);*/
	/*if (a == J)
		ft_write(s);*/
	if (a == 13 || a == 0 || a == 1 || a == 2)
		ft_dep(a, s);
	else 
		printf("touch pressee: %d\n", a);
	return (1);
}

int		main(int argc, char **argv)
{
	t_cub 	c;
	t_map	m;
	int		err;

	int i;
	
	if (check_args(argc, argv) < 0)
		return (1);
	ft_init_map(&c, &m);
	if ((err = ft_map(&m, &c, argv[1])))
	{
		free_struct(&m);
		//system("leaks exec.out");
		return(ft_errors(err));
	}

	printf("res_width ==> |%d|\n", c.win_width);
	printf("res_height ==> |%d|\n", c.win_height);	
	printf("no    ==> |%s|\n", m.no);
	printf("so    ==> |%s|\n", m.so);
	printf("we    ==> |%s|\n", m.we);
	printf("ea    ==> |%s|\n", m.ea);
	printf("sprit ==> |%s|\n", m.sprite);
	printf("floor ==> |%d|\n", m.floor);
	printf("ceil  ==> |%d|\n", m.ceil);
	i = 0;
	printf("map :\n");
	while(m.m[i])
		printf("|%s|\n", m.m[i++]);
	printf("mapWeight     ==> |%d|\n", m.m_w);
	printf("mapHeight     ==> |%d|\n", m.m_h);
	printf("start ==> |%c|\n", m.start);
	printf("s_x     ==> |%f|\n", m.s_x);
	printf("s_y     ==> |%f|\n", m.s_y);
	//free_struct(&m);
	//system("leaks exec.out");
	c.m = &m;
	c.t = "Cub3D";
	//m.s_x = 1.5;
	//m.s_y = 1.2;
	//c.x_test = 0;
	//c.y_test = 0;
	if (!(c.mlx_ptr = mlx_init()))
		exit(1);
	if (!(c.win_ptr = mlx_new_window(c.mlx_ptr, c.win_width, c.win_height, c.t)))
		exit(1);
	draw_map(&c);	
	//mlx_loop_hook(c.mlx_ptr, draw_map, &c);
	mlx_hook(c.win_ptr, KPRESS, 0, ft_key_event, &c);
	//Close the window with the button
	mlx_hook(c.win_ptr, 17, 0, ft_exit_button, &c);
	mlx_loop(c.mlx_ptr);
	ft_exit_esc(&c);
	return (0);
}