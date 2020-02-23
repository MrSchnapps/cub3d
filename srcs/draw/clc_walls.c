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

void    clc_side_dest(t_cub *c)
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



void    clc_dist_hit(t_cub *c)
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
	c->clc.lineHeight = (int)(c->win_h / c->clc.pwd);
	c->clc.drawStart = (c->win_h / 2) - (c->clc.lineHeight / 2);
	if (c->clc.drawStart < 0)
		c->clc.drawStart = 0;
	c->clc.drawEnd = (c->clc.lineHeight / 2) + (c->win_h / 2);
	if (c->clc.drawEnd >= c->win_h)
		c->clc.drawEnd = c->win_h - 1;
}

void	clc_text(t_cub *c)
{
	if (c->clc.side == 0)
		c->clc.wallX = c->m->pos_x + c->clc.pwd * c->clc.rdy;
	else
		c->clc.wallX = c->m->pos_y + c->clc.pwd * c->clc.rdx;
	c->clc.wallX -= floor(c->clc.wallX);
	c->clc.texX = (int)(c->clc.wallX * (double)TEXTWIDTH);
	if (c->clc.side == 0 && c->clc.rdx > 0)
		c->clc.texX = TEXTWIDTH - c->clc.texX - 1;
	if (c->clc.side == 1 && c->clc.rdy < 0)
		c->clc.texX = TEXTWIDTH - c->clc.texX - 1;
	c->clc.step = 1.0 * TEXTHEIGHT / c->clc.lineHeight;
	c->clc.textPos = (c->clc.drawStart - c->win_h / 2 + 
						c->clc.lineHeight / 2) * c->clc.step;
}

