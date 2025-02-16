/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:24:00 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 17:09:32 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	find_side(t_cub *c, int id)
{
	c->clc.hit = 1;
	if (c->mpx != c->clc.map_x || c->mpy != c->clc.map_y)
		c->bords = 1;
	c->mpx = c->clc.map_x;
	c->mpy = c->clc.map_y;
	if (id == 1)
	{
		if (c->clc.text_num == 2 || c->clc.text_num == 3)
			c->bords = 1;
		c->clc.text_num = (c->clc.rdx < 0) ? 1 : 0;
	}
	else
	{
		if (c->clc.text_num == 1 || c->clc.text_num == 0)
			c->bords = 1;
		c->clc.text_num = (c->clc.rdy < 0) ? 2 : 3;
	}
}
