/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:36:53 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 16:52:05 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_exit_button(t_cub *c)
{
	return (ft_exit(c, 0));
}

int		ft_exit(t_cub *c, int ret)
{
	fpf(1, "Cleaning memory ...\n");
	free_struct(c->m);
	(c->img_ptr) ? mlx_destroy_image(c->mlx_ptr, c->img_ptr) : 0;
	(c->wall_n) ? mlx_destroy_image(c->mlx_ptr, c->wall_n) : 0;
	(c->wall_s) ? mlx_destroy_image(c->mlx_ptr, c->wall_s) : 0;
	(c->wall_e) ? mlx_destroy_image(c->mlx_ptr, c->wall_e) : 0;
	(c->wall_w) ? mlx_destroy_image(c->mlx_ptr, c->wall_w) : 0;
	(c->sprite1) ? mlx_destroy_image(c->mlx_ptr, c->sprite1) : 0;
	free(c->sprt.asprt);
	free(c->sprt.zbuffer);
	free(c->sprt.sprite_order);
	free(c->sprt.sprite_distance);
	(c->win_ptr) ? mlx_clear_window(c->mlx_ptr, c->win_ptr) : 0;
	(c->win_ptr) ? mlx_destroy_window(c->mlx_ptr, c->win_ptr) : 0;
	fpf(1, "Memory Clean !!\n");
	exit(ret);
	return (ret);
}
