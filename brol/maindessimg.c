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

int	ft_draw(t_cub *s, int a)
{
	int		i;
	int		*color;
	int		id;

	i = 0;
	color = (int *)mlx_get_data_addr(s->img_ptr, &id, &id, &id);
	if (a == 124)
	{
		printf("touche droite pressee\n");
		color[(1000 * s->y_test) + s->x_test] = RED;
		//mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
		//mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x_test, s->y_test, RED);
		s->x_test++;
	}
	if (a == 125)
	{
		printf("touche bas pressee\n");
		//mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x_test, s->y_test, GREEN);
		//s->y_test = (1000 * s->y_test) + s->x_test;
		color[(1000 * s->y_test) + s->x_test] = s->m->floor;
		//mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
		s->y_test++;
	}
	if (a == 123)
	{
		printf("touche gauche pressee\n");
		//mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x_test, s->y_test, BLUE);
		color[(1000 * s->y_test) + s->x_test] = s->m->floor;
		//mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
		s->x_test--;
	}
	if (a == 126)
	{
		printf("touche haut pressee\n");
		//mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x_test, s->y_test, ORANGE);
		color[(1000 * s->y_test) + s->x_test] = s->m->floor;
		//mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
		s->y_test--;
	}
	//afficher image
	if (a == 0)
	{
		/*printf("touche haut pressee\n");
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x_test, s->y_test, ORANGE);
		s->y_test--;*/
		printf("\naaaaaaaaaaaaaa\n");
		mlx_put_image_to_window(s->mlx_ptr, s->win_ptr, s->img_ptr, 0, 0);
	}
	return (1);
}

int ft_write(t_cub *s)
{
	mlx_string_put(s->mlx_ptr, s->win_ptr, 200, 250, ORANGE, "JULES");
	return (1);
}

int ft_key_event(int a, t_cub *s)
{
	if (a == ESC)
		ft_exit_esc(s);
	if ((a >= 123 && a <= 126) || a == 0)
		ft_draw(s, a);
	if (a == J)
		ft_write(s);
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

int main(int argc, char **argv)
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
	free_struct(&m);
	//system("leaks exec.out");
	c.m = &m;
	c.t = "Cub3D";
	c.x_test = 0;
	c.y_test = 0;
	
	if (!(c.mlx_ptr = mlx_init()))
		exit(0);
	if (!(c.win_ptr = mlx_new_window(c.mlx_ptr, c.x, c.y, c.t)))
		exit(0);
	c.img_ptr = mlx_new_image(c.mlx_ptr, c.x, c.y);
	mlx_hook(c.win_ptr, KPRESS, 0, ft_key_event, &c);
	//Close the window with the button
	mlx_hook(c.win_ptr, 17, 0, ft_exit_button, &c);
	mlx_loop(c.mlx_ptr);
	return (0);
}