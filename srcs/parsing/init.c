/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:19:17 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/20 19:51:00 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_nsew(t_map *map, int i, int j)
{
	if (map->m[i][j] == 'N' || map->m[i][j] == 'S')
	{
		map->dx = (map->m[i][j] == 'N') ? -1 : 1;
		map->dy = 0;
		map->px = 0;
		map->py = (map->m[i][j] == 'N') ? 0.66 : -0.66;
		
	}
	else
	{
		map->dx = 0;
		map->dy = (map->m[i][j] == 'E') ? 1 : -1;
		map->px = (map->m[i][j] == 'E') ? 0.66 : -0.66;
		map->py = 0;
	}
	map->start = map->m[i][j];
	map->pos_x = j + 0.5;
	map->pos_y = i + 0.5;
}

void	init_map(t_map *map)
{
	map->no = NULL;
	map->so	= NULL;
	map->we = NULL;
	map->ea = NULL;
	map->sprite = NULL;
	map->floor = -1;
	map->ceil = -1;
	map->m = NULL;
	map->start = 0;
	map->m_w = 0;
	map->m_h = 0;
	map->dx = 1;
	map->dy = 0;
	map->px = 0;
	map->py = -0.66;
	map->nb_sprites = 0;
}

void	ft_init(t_cub *c, t_map *map)
{
	c->mlx_ptr = NULL;
	c->win_ptr = NULL;
	c->img_ptr = NULL;
	c->wall_n = NULL;
	c->wall_s = NULL;
	c->wall_e = NULL;
	c->wall_w = NULL;
	c->sprite1 = NULL;
	c->win_w = -1;
	c->win_h = -1;
	c->textures = 1;
	c->clc.text_num = 5;
	c->sprt.asprt = NULL;
	c->sprt.zbuffer = NULL;
	c->sprt.sprite_order = NULL;
	c->sprt.sprite_distance = NULL;
	c->save = 0;
	init_map(map);	
}