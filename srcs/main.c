#include "cub3d.h"

//Regler les noms de fonctions et variables a la norme
void	print_test(t_cub *c, t_map *m)
{
	int i;

	i = 0;
	printf("res_width ==> |%d|\n", c->win_width);
	printf("res_height ==> |%d|\n", c->win_height);	
	printf("no    ==> |%s|\n", m->no);
	printf("so    ==> |%s|\n", m->so);
	printf("we    ==> |%s|\n", m->we);
	printf("ea    ==> |%s|\n", m->ea);
	printf("sprit ==> |%s|\n", m->sprite);
	printf("floor ==> |%d|\n", m->floor);
	printf("ceil  ==> |%d|\n", m->ceil);
	printf("map :\n");
	while(m->m[i])
		printf("|%s|\n", m->m[i++]);
	printf("mapWeight     ==> |%d|\n", m->m_w);
	printf("mapHeight     ==> |%d|\n", m->m_h);
	printf("start ==> |%c|\n", m->start);
	printf("s_x     ==> |%f|\n", m->pos_x);
	printf("s_y     ==> |%f|\n", m->pos_y);
	//printf("test ==> x => |%f|\n", c->sprt.all_sprites[0].x);
}

int		set_mlx(t_cub *c)
{
	int	w;
	int	h;
	int id;

	w = 64;
	h = 64;
	if (!(c->win_ptr = mlx_new_window(c->mlx_ptr, c->win_width, c->win_height, c->t)))
		return (21);
	if (!(c->img_ptr = mlx_new_image(c->mlx_ptr, c->win_width, c->win_height)))
		return (22);
	if ((!(c->wall_n = mlx_xpm_file_to_image(c->mlx_ptr, c->m->no, &w, &h)))
		|| (!(c->wall_s = mlx_xpm_file_to_image(c->mlx_ptr, c->m->so, &w, &h)))
		|| (!(c->wall_e = mlx_xpm_file_to_image(c->mlx_ptr, c->m->ea, &w, &h)))
		|| (!(c->wall_w = mlx_xpm_file_to_image(c->mlx_ptr, c->m->we, &w, &h)))
		|| (!(c->sprite1 =  mlx_xpm_file_to_image(c->mlx_ptr, c->m->sprite, &w, &h))))
		return (23);
	c->tab_text[0] = (int *)mlx_get_data_addr(c->wall_n, &id, &id, &id);
	c->tab_text[1] = (int *)mlx_get_data_addr(c->wall_s, &id, &id, &id);
	c->tab_text[2] = (int *)mlx_get_data_addr(c->wall_e, &id, &id, &id);
	c->tab_text[3] = (int *)mlx_get_data_addr(c->wall_w, &id, &id, &id);
	c->addr_sprite = (int *)mlx_get_data_addr(c->sprite1, &id, &id, &id);
	c->pix = (int *)mlx_get_data_addr(c->img_ptr, &id, &id, &id);
	return (0);
}

int		main(int argc, char **argv)
{
	int		err;
	t_cub 	c;
	t_map	m;

	c.t = "Cub3D";
	c.m = &m;
	ft_init(&c, &m);
	if ((err = check_args(argc, argv, &c)))
		return (ft_errors(err, &c, 1));
	if ((err = ft_map(&m, &c, argv[1])))
		return(ft_errors(err, &c, 1));
	if ((err = ft_get_sprites(&m, &c)))
		return (ft_errors(err, &c, 1));
	print_test(&c, &m);
	if (!(c.mlx_ptr = mlx_init()))
		return (ft_errors(20, &c, 1));
	if ((err = set_mlx(&c)))
		return (ft_errors(err, &c, 1));
	draw_map(&c);
	mlx_hook(c.win_ptr, KPRESS, 0, ft_key_event, &c);
	mlx_hook(c.win_ptr, 17, 0, ft_exit_button, &c);
	mlx_loop(c.mlx_ptr);
	ft_exit(&c, 0);
	return (0);
}