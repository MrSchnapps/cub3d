/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc_sprites.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:12:02 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 15:14:42 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sort_sprite(int *sprite_order, double *sprite_distance, int nb_sprites)
{
	int		i;
	int		is_sort;
	int		tmp_order;
	double	tmp_dist;

	is_sort = 0;
	while (!is_sort)
	{
		is_sort = 1;
		i = -1;
		while (++i < nb_sprites - 1)
			if (sprite_distance[i] < sprite_distance[i + 1])
			{
				tmp_dist = sprite_distance[i];
				tmp_order = sprite_order[i];
				sprite_distance[i] = sprite_distance[i + 1];
				sprite_order[i] = sprite_order[i + 1];
				sprite_distance[i + 1] = tmp_dist;
				sprite_order[i + 1] = tmp_order;
				is_sort = 0;
			}
	}
}

void	set_clc(t_cub *c, int i)
{
	c->sprt.sprite_x = c->sprt.asprt[c->sprt.sprite_order[i]].y - c->m->pos_y;
	c->sprt.sprite_y = c->sprt.asprt[c->sprt.sprite_order[i]].x - c->m->pos_x;
	c->sprt.inv_det = 1.0 / (c->m->px * c->m->dy - c->m->dx * c->m->py);
	c->sprt.trsfm_x = c->sprt.inv_det *
				(c->m->dy * c->sprt.sprite_x - c->m->dx * c->sprt.sprite_y);
	c->sprt.trsfm_y = c->sprt.inv_det *
				(-c->m->py * c->sprt.sprite_x + c->m->px * c->sprt.sprite_y);
	c->sprt.screen_x = (int)((c->win_w / 2) *
				(1 + c->sprt.trsfm_x / c->sprt.trsfm_y));
	c->sprt.sprite_height = abs((int)(c->win_h / c->sprt.trsfm_y));
	c->sprt.draw_start_y = -c->sprt.sprite_height / 2 + c->win_h / 2;
	if (c->sprt.draw_start_y < 0)
		c->sprt.draw_start_y = 0;
	c->sprt.draw_end_y = c->sprt.sprite_height / 2 + c->win_h / 2;
	if (c->sprt.draw_end_y >= c->win_h)
		c->sprt.draw_end_y = c->win_h - 1;
	c->sprt.sprite_width = abs((int)(c->win_h / c->sprt.trsfm_y));
	c->sprt.draw_start_x = -c->sprt.sprite_width / 2 + c->sprt.screen_x;
	if (c->sprt.draw_start_x < 0)
		c->sprt.draw_start_x = 0;
	c->sprt.draw_end_x = c->sprt.sprite_width / 2 + c->sprt.screen_x;
	if (c->sprt.draw_end_x >= c->win_w)
		c->sprt.draw_end_x = c->win_w - 1;
	c->sprt.stripe = c->sprt.draw_start_x;
}

void	clc_sprites(t_cub *c)
{
	int	i;

	i = -1;
	while (++i < c->m->nb_sprites)
	{
		c->sprt.sprite_order[i] = i;
		c->sprt.sprite_distance[i] = (((double)c->m->pos_y -
										c->sprt.asprt[i].y) *
									((double)c->m->pos_y -
										c->sprt.asprt[i].y) +
									((double)c->m->pos_x -
										c->sprt.asprt[i].x) *
									((double)c->m->pos_x -
										c->sprt.asprt[i].x));
	}
	sort_sprite(c->sprt.sprite_order, c->sprt.sprite_distance,
		c->m->nb_sprites);
	i = -1;
	while (++i < c->m->nb_sprites)
	{
		set_clc(c, i);
		draw_sprites(c);
	}
}
