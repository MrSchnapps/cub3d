#include "cub3d.h"

//Regler les noms de fonctions et variables a la norme

int		main(int argc, char **argv)
{
	t_cub 	c;
	t_map	m;
	int		err;
	int 	id;
	int 	i;
	int 	w;
	int 	h;

	w = 64;
	h = 64;
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
	printf("s_x     ==> |%f|\n", m.pos_x);
	printf("s_y     ==> |%f|\n", m.pos_y);
	c.m = &m;
	c.t = "Cub3D";
	printf("========> |%f|\n", -W_PROTECT);

	
	test(&c);
	printf("test ==> x => |%f|\n", c.sprt.all_sprites[0].x);
	
	if (!(c.mlx_ptr = mlx_init()))
		exit(1);
	if (!(c.win_ptr = mlx_new_window(c.mlx_ptr, c.win_width, c.win_height, c.t)))
		exit(1);
	if (!(c.img_ptr = mlx_new_image(c.mlx_ptr, c.win_width, c.win_height)))
		exit(1);
	
	c.wall_n = mlx_xpm_file_to_image(c.mlx_ptr, c.m->no, &w, &h);
	c.wall_s = mlx_xpm_file_to_image(c.mlx_ptr, c.m->so, &w, &h);
	c.wall_e = mlx_xpm_file_to_image(c.mlx_ptr, c.m->ea, &w, &h);
	c.wall_w = mlx_xpm_file_to_image(c.mlx_ptr, c.m->we, &w, &h);
	c.sprite1 =  mlx_xpm_file_to_image(c.mlx_ptr, c.m->sprite, &w, &h);

	c.tab_text[0] = (int *)mlx_get_data_addr(c.wall_n, &id, &id, &id);
	c.tab_text[1] = (int *)mlx_get_data_addr(c.wall_s, &id, &id, &id);
	c.tab_text[2] = (int *)mlx_get_data_addr(c.wall_e, &id, &id, &id);
	c.tab_text[3] = (int *)mlx_get_data_addr(c.wall_w, &id, &id, &id);
	c.pix = (int *)mlx_get_data_addr(c.img_ptr, &id, &id, &id);
	draw_map(&c);
	//mlx_loop_hook(c.mlx_ptr, draw_map, &c);
	mlx_hook(c.win_ptr, KPRESS, 0, ft_key_event, &c);
	//Close the window with the button
	mlx_hook(c.win_ptr, 17, 0, ft_exit_button, &c);
	mlx_loop(c.mlx_ptr);
	
	ft_exit_esc(&c);
	return (0);
}