#include "../includes/cubd.h"


/*int	ft_exit_button(t_cubd *s)
{
	printf("on a appuye sur la croix\n");
	mlx_clear_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	exit(0);
	return (1);
}

int	ft_exit_esc(t_cubd *s)
{
	printf("on a appuye sur ESC\n");
	mlx_clear_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	exit(0);
	return (1);
}

int	ft_draw(t_cubd *s, int a)
{
	if (a == 124)
	{
		printf("touche droite pressee\n");
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x, s->y, RED);
		s->x++;
	}
	if (a == 125)
	{
		printf("touche bas pressee\n");
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x, s->y, GREEN);
		s->y++;
	}
	if (a == 123)
	{
		printf("touche gauche pressee\n");
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x, s->y, BLUE);
		s->x--;
	}
	if (a == 126)
	{
		printf("touche haut pressee\n");
		mlx_pixel_put(s->mlx_ptr, s->win_ptr, s->x, s->y, ORANGE);
		s->y--;
	}
	return (1);
}

int ft_write(t_cubd *s)
{
	mlx_string_put(s->mlx_ptr, s->win_ptr, 200, 250, ORANGE, "JULES");
	return (1);
}

int ft_key_event(int a, t_cubd *s)
{
	if (a == ESC)
		ft_exit_esc(s);
	if (a >= 123 && a <= 126)
		ft_draw(s, a);
	if (a == J)
		ft_write(s);
	else 
		printf("touch pressee: %d\n", a);
	return (1);
}*/

int main(int argc, char **argv)
{
	//t_cubd 	s;
	t_map	m;
	int		err;
	//int		size_x;		
	//int		size_y;
	//char 	*title;
	
	if (check_args(argc, argv) < 0)
		return (1);
	ft_init_map(&m);
	if ((err = ft_map(&m, argv[1])))
		return(ft_errors(err));
	/*title = "Cub3D";
	size_x = 800;
	size_y = 800;
	s.x = 0;
	s.y = 0;
	if (!(s.mlx_ptr = mlx_init()))
		exit(0);
	if (!(s.win_ptr = mlx_new_window(s.mlx_ptr, size_x, size_y, title)))
		exit(0);
	mlx_hook(s.win_ptr, KPRESS, 0, ft_key_event, &s);*/
	
	//Close the window with the button
	//mlx_hook(s.win_ptr, 17, 0, ft_exit_button, &s);
	//mlx_loop(s.mlx_ptr);
	return (0);
}