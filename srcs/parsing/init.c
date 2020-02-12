/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:19:17 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/12 22:00:29 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_map(t_cub *c, t_map *map)
{
	//map->res_x = -1;
	//map->res_y = -1;
	c->win_width = -1;
	c->win_height = -1;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->sprite = NULL;
	map->floor = -1;
	map->ceil = -1;
	map->m = NULL;
	map->start = 0;
	map->m_w = 0;
	map->m_h = 0;
	map->s_x = 0;
	map->s_y = 0;
	map->dx = 0;
	map->dy = -1;
	map->px = -0.66;
	map->py = 0;
}