#include "cub3d.h"

int	ft_exit_button(t_cub *s)
{
	printf("on a appuye sur la croix\n");
	free_struct(s->m);
	(s->img_ptr) ? mlx_destroy_image(s->mlx_ptr, s->img_ptr) : 0;
	(s->wall_n) ? mlx_destroy_image(s->mlx_ptr, s->wall_n) : 0;
	(s->wall_s) ? mlx_destroy_image(s->mlx_ptr, s->wall_s) : 0;
	(s->wall_e) ? mlx_destroy_image(s->mlx_ptr, s->wall_e) : 0;
	(s->wall_w) ? mlx_destroy_image(s->mlx_ptr, s->wall_w) : 0;
	(s->sprite1) ? mlx_destroy_image(s->mlx_ptr, s->sprite1) : 0;
	free(s->sprt.all_sprites);
	mlx_clear_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	exit(0);
	return (1);
}

int	ft_exit_esc(t_cub *s)
{
	printf("on a appuye sur ESC\n");
	free_struct(s->m);
	(s->img_ptr) ? mlx_destroy_image(s->mlx_ptr, s->img_ptr) : 0;
	(s->wall_n) ? mlx_destroy_image(s->mlx_ptr, s->wall_n) : 0;
	(s->wall_s) ? mlx_destroy_image(s->mlx_ptr, s->wall_s) : 0;
	(s->wall_e) ? mlx_destroy_image(s->mlx_ptr, s->wall_e) : 0;
	(s->wall_w) ? mlx_destroy_image(s->mlx_ptr, s->wall_w) : 0;
	(s->sprite1) ? mlx_destroy_image(s->mlx_ptr, s->sprite1) : 0;
	free(s->sprt.all_sprites);
	mlx_clear_window(s->mlx_ptr, s->win_ptr);
	mlx_destroy_window(s->mlx_ptr, s->win_ptr);
	exit(0);
	return (1);
}