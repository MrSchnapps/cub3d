/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:40:41 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 16:47:24 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		load_img(t_cub *c)
{
	int	w;
	int	h;
	int id;

	if ((!(c->wall_n = mlx_xpm_file_to_image(c->mlx_ptr, c->m->no, &w, &h)))
		|| (!(c->wall_s = mlx_xpm_file_to_image(c->mlx_ptr, c->m->so, &w, &h)))
		|| (!(c->wall_e = mlx_xpm_file_to_image(c->mlx_ptr, c->m->ea, &w, &h)))
		|| (!(c->wall_w = mlx_xpm_file_to_image(c->mlx_ptr, c->m->we, &w, &h)))
		|| (!(c->sprite1 = mlx_xpm_file_to_image(c->mlx_ptr,
			c->m->sprite, &w, &h))))
		return (23);
	if (!(c->t_text[0] = (int *)mlx_get_data_addr(c->wall_n, &id, &id, &id))
		|| !(c->t_text[1] = (int *)mlx_get_data_addr(c->wall_s, &id, &id, &id))
		|| !(c->t_text[2] = (int *)mlx_get_data_addr(c->wall_e, &id, &id, &id))
		|| !(c->t_text[3] = (int *)mlx_get_data_addr(c->wall_w, &id, &id, &id))
		|| !(c->ad_sprt = (int *)mlx_get_data_addr(c->sprite1, &id, &id, &id)))
		return (23);
	return (0);
}

int		set_mlx(t_cub *c)
{
	int id;

	if (!c->save)
	{
		if (!(c->win_ptr = mlx_new_window(c->mlx_ptr, c->win_w, c->win_h,
			c->t)))
			return (21);
	}
	if (!(c->img_ptr = mlx_new_image(c->mlx_ptr, c->win_w, c->win_h)))
		return (22);
	if (!(c->pix = (int *)mlx_get_data_addr(c->img_ptr, &id, &id, &id)))
		return (22);
	return (load_img(c));
}

int		main(int argc, char **argv)
{
	int		err;
	t_cub	c;
	t_map	m;

	c.t = "Cub3D";
	c.m = &m;
	ft_init(&c, &m);
	if ((err = check_args(argc, argv, &c)))
		return (ft_errors(err, &c, 1));
	if ((err = ft_map(&m, &c, argv[1])))
		return (ft_errors(err, &c, 1));
	if ((err = ft_get_sprites(&m, &c)))
		return (ft_errors(err, &c, 1));
	if (!(c.mlx_ptr = mlx_init()))
		return (ft_errors(20, &c, 1));
	if ((err = set_mlx(&c)))
		return (ft_errors(err, &c, 1));
	draw_map(&c);
	mlx_hook(c.win_ptr, KPRESS, 0, ft_key_event, &c);
	mlx_hook(c.win_ptr, 17, 0, ft_exit_button, &c);
	mlx_loop(c.mlx_ptr);
	return (ft_exit(&c, 0));
}
