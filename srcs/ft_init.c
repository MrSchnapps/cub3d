/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:19:17 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/04 22:30:58 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubd.h"

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
}