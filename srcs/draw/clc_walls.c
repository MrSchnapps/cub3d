/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clc_walls.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:15:14 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 16:09:53 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_inf_map(t_cub *c, int x)
{
	c->clc.camera_x = 2 * x / (double)c->win_w - 1;
	c->clc.rdx = c->m->dx + c->m->px * c->clc.camera_x;
	c->clc.rdy = c->m->dy + c->m->py * c->clc.camera_x;
	c->clc.map_x = (int)c->m->pos_y;
	c->clc.map_y = (int)c->m->pos_x;
	c->clc.dlt_dx = fabs(1 / c->clc.rdx);
	c->clc.dlt_dy = fabs(1 / c->clc.rdy);
}

void	clc_side_dest(t_cub *c)
{
	if (c->clc.rdx < 0)
	{
		c->clc.stepx = -1;
		c->clc.sdx = (c->m->pos_y - c->clc.map_x) * c->clc.dlt_dx;
	}
	else
	{
		c->clc.stepx = 1;
		c->clc.sdx = (c->clc.map_x + 1.0 - c->m->pos_y) * c->clc.dlt_dx;
	}
	if (c->clc.rdy < 0)
	{
		c->clc.stepy = -1;
		c->clc.sdy = (c->m->pos_x - c->clc.map_y) * c->clc.dlt_dy;
	}
	else
	{
		c->clc.stepy = 1;
		c->clc.sdy = (c->clc.map_y + 1.0 - c->m->pos_x) * c->clc.dlt_dy;
	}
}

void	clc_dist_hit(t_cub *c)
{
	c->clc.hit = 0;
	while (c->clc.hit == 0)
	{
		c->bords = 0;
		if (c->clc.sdx < c->clc.sdy)
		{
			c->clc.sdx += c->clc.dlt_dx;
			c->clc.map_x += c->clc.stepx;
			c->clc.side = 0;
			if (c->m->m[c->clc.map_x][c->clc.map_y] == '1')
				find_side(c, 1);
		}
		else
		{
			c->clc.sdy += c->clc.dlt_dy;
			c->clc.map_y += c->clc.stepy;
			c->clc.side = 1;
			if (c->m->m[c->clc.map_x][c->clc.map_y] == '1')
				find_side(c, 2);
		}
	}
}

void	clc_start_end(t_cub *c)
{
	if (c->clc.side == 0)
		c->clc.pwd = (c->clc.map_x - c->m->pos_y +
		(1 - c->clc.stepx) / 2) / c->clc.rdx;
	else
		c->clc.pwd = (c->clc.map_y - c->m->pos_x +
		(1 - c->clc.stepy) / 2) / c->clc.rdy;
	c->clc.line_h = (int)(c->win_h / c->clc.pwd);
	c->clc.d_start = (c->win_h / 2) - (c->clc.line_h / 2);
	if (c->clc.d_start < 0)
		c->clc.d_start = 0;
	c->clc.d_end = (c->clc.line_h / 2) + (c->win_h / 2);
	if (c->clc.d_end >= c->win_h)
		c->clc.d_end = c->win_h - 1;
}

void	clc_text(t_cub *c)
{
	if (c->clc.side == 0)
		c->clc.wall_x = c->m->pos_x + c->clc.pwd * c->clc.rdy;
	else
		c->clc.wall_x = c->m->pos_y + c->clc.pwd * c->clc.rdx;
	c->clc.wall_x -= floor(c->clc.wall_x);
	c->clc.texx = (int)(c->clc.wall_x * (double)TEXTWIDTH);
	if (c->clc.side == 0 && c->clc.rdx > 0)
		c->clc.texx = TEXTWIDTH - c->clc.texx - 1;
	if (c->clc.side == 1 && c->clc.rdy < 0)
		c->clc.texx = TEXTWIDTH - c->clc.texx - 1;
	c->clc.step = 1.0 * TEXTHEIGHT / c->clc.line_h;
	c->clc.text_pos = (c->clc.d_start - c->win_h / 2 +
						c->clc.line_h / 2) * c->clc.step;
}
