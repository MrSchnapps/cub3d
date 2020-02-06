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

int ft_key_event(int a, t_cub *s)
{
	if (a == ESC)
		ft_exit_esc(s);
	/*if ((a >= 123 && a <= 126) || a == 0)
		ft_draw(s, a);*/
	/*if (a == J)
		ft_write(s);*/
	else 
		printf("touch pressee: %d\n", a);
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

void vertLine(int drawStart, int drawEnd, t_cub *c)
{
	int	*pix;
	int	id;

	printf("\nStart ==> |%d|\nEnd ==> |%d|\n", drawStart, drawEnd);
	pix = (int *)mlx_get_data_addr(c->img_ptr, &id, &id, &id);
	while (drawStart > drawEnd)
	{
		pix[drawStart] = ORANGE;
		drawStart -= c->x;
		mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	}
}

int		draw_map(t_cub *c)
{
	int		i;
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

	c->img_ptr = mlx_new_image(c->mlx_ptr, c->x, c->y);
	done = 1;
	i = 0;
	while (i < c->x)
	{
		camera_x = 2 * i / (double)c->x - 1;
		ray_dir_x = c->m->dx + c->m->px * camera_x;
		ray_dir_y = c->m->dy + c->m->py * camera_x;

		map_x = (int)c->m->s_y;
		map_y = (int)c->m->s_x;

		deltaDistX = absolute(1 / ray_dir_x);
		deltaDistY = absolute(1 / ray_dir_y);

		hit = 0;
		if (ray_dir_x < 0)
		{
			stepX = -1;
			sideDistX = (c->m->s_x - map_x) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (map_x + 1.0 - c->m->s_x) * deltaDistX;
		}
		if (ray_dir_y < 0)
		{
			stepY = -1;
			sideDistY = (c->m->s_y - map_y) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (map_y + 1.0 - c->m->s_y) * deltaDistY;
		}
		while (hit == 0)
		{
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				map_x += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				map_y += stepY;
				side = 1;
			}
			if (c->m->m[map_x][map_y] == '1') 
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (map_x - c->m->s_x + (1 - stepX) / 2) / ray_dir_x;
		else
			perpWallDist = (map_y - c->m->s_y + (1 - stepY) / 2) / ray_dir_y;
		lineHeight = (int)(c->y / perpWallDist);
		drawStart = -lineHeight / 2 + c->y / 2;
		if (drawStart < 0)
			drawStart = 0;
		drawEnd = lineHeight / 2 + c->x / 2;
		if (drawEnd >= c->m->x)
			drawEnd = c->m->x - 1;
		vertLine(drawStart, drawEnd, c);
		i++;
	}
	return (0);
}

int		main(int argc, char **argv)
{
	t_cub 	c;
	t_map	m;
	int		err;

	int i;
	
	if (check_args(argc, argv) < 0)
		return (1);
	ft_init_map(&m);
	if ((err = ft_map(&m, &c, argv[1])))
	{
		free_struct(&m);
		//system("leaks exec.out");
		return(ft_errors(err));
	}

	printf("res_x ==> |%d|\n", m.res_x);
	printf("res_y ==> |%d|\n", m.res_y);
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
	printf("x     ==> |%d|\n", c.x);
	printf("y     ==> |%d|\n", c.y);
	printf("start ==> |%c|\n", m.start);
	printf("s_x     ==> |%f|\n", m.s_x);
	printf("s_y     ==> |%f|\n", m.s_y);
	//free_struct(&m);
	//system("leaks exec.out");
	c.m = &m;
	c.t = "Cub3D";
	//c.x_test = 0;
	//c.y_test = 0;
	printf("\ncoucoucoucocucucoucou\n");
	if (!(c.mlx_ptr = mlx_init()))
		exit(1);
	if (!(c.win_ptr = mlx_new_window(c.mlx_ptr, c.x, c.y, c.t)))
		exit(1);
	if (!(c.img_ptr = mlx_new_image(c.mlx_ptr, c.x, c.y)))
		exit(1);
	mlx_loop_hook(c.mlx_ptr,draw_map, &c);
	mlx_hook(c.win_ptr, KPRESS, 0, ft_key_event, &c);
	//Close the window with the button
	mlx_hook(c.win_ptr, 17, 0, ft_exit_button, &c);
	mlx_loop(c.mlx_ptr);
	ft_exit_esc(&c);
	return (0);
}