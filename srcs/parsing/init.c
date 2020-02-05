/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:19:17 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/05 16:59:24 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_init_map(t_map *map)
{
	map->res_x = -1;
	map->res_y = -1;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->sprite = NULL;
	map->floor = -1;
	map->ceil = -1;
	map->m = NULL;
	map->start = 0;
	map->x = 0;
	map->y = 0;
	map->s_x = 0;
	map->s_y = 0;
}