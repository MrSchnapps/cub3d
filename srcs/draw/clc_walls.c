#include "cub3d.h"

void	set_inf_map(t_cub *c, int x)
{
	c->clc.camera_x = 2 * x / (double)c->win_width - 1;
	c->clc.ray_dir_x = c->m->dx + c->m->px * c->clc.camera_x;
	c->clc.ray_dir_y = c->m->dy + c->m->py * c->clc.camera_x;
	c->clc.map_x = (int)c->m->pos_y;
	c->clc.map_y = (int)c->m->pos_x;
	c->clc.deltaDistX = fabs(1 / c->clc.ray_dir_x);
	c->clc.deltaDistY = fabs(1 / c->clc.ray_dir_y);
}

void    clc_side_dest(t_cub *c)
{
	if (c->clc.ray_dir_x < 0)
	{
		c->clc.stepX = -1;
		c->clc.sideDistX = (c->m->pos_y - c->clc.map_x) * c->clc.deltaDistX;
	}
	else
	{
		c->clc.stepX = 1;
		c->clc.sideDistX = (c->clc.map_x + 1.0 - c->m->pos_y) * c->clc.deltaDistX;
	}
	if (c->clc.ray_dir_y < 0)
	{
		c->clc.stepY = -1;
		c->clc.sideDistY = (c->m->pos_x - c->clc.map_y) * c->clc.deltaDistY;
	}
	else
	{
		c->clc.stepY = 1;
		c->clc.sideDistY = (c->clc.map_y + 1.0 - c->m->pos_x) * c->clc.deltaDistY;
	}
}

void    clc_dist_hit(t_cub *c)
{
	c->clc.hit = 0;
	while (c->clc.hit == 0)
	{
		c->bords = 0;
		if (c->clc.sideDistX < c->clc.sideDistY)
		{
			c->clc.sideDistX += c->clc.deltaDistX;
			c->clc.map_x += c->clc.stepX;
			c->clc.side = 0;

			if (c->m->m[c->clc.map_x][c->clc.map_y] == '1') 
			{	
				c->clc.hit = 1;
				if (c->mpx != c->clc.map_x || c->mpy != c->clc.map_y)
					c->bords = 1;
				c->mpx = c->clc.map_x;
				c->mpy = c->clc.map_y;
				if (c->clc.text_num == 2|| c->clc.text_num == 3)
					c->bords = 1;
				c->clc.text_num = (c->clc.ray_dir_x < 0) ? 0 : 1;
			}
		}
		else
		{
			if (c->clc.sideDistX == c->clc.sideDistY)
				c->bords = 1;
			c->clc.sideDistY += c->clc.deltaDistY;
			c->clc.map_y += c->clc.stepY;
			c->clc.side = 1;
			if (c->m->m[c->clc.map_x][c->clc.map_y] == '1') 
			{
				c->clc.hit = 1;
				if (c->mpx != c->clc.map_x || c->mpy != c->clc.map_y)
					c->bords = 1;
				c->mpx = c->clc.map_x;
				c->mpy = c->clc.map_y;
				if (c->clc.text_num == 1 || c->clc.text_num == 0)
					c->bords = 1;

				c->clc.text_num = (c->clc.ray_dir_y < 0) ? 2 : 3;
			}
		}
		/*if (c->m->m[c->clc.map_x][c->clc.map_y] == '1') 
			c->clc.hit = 1;*/
	}
}

void	clc_start_end(t_cub *c)
{
	if (c->clc.side == 0)
		c->clc.perpWallDist = (c->clc.map_x - c->m->pos_y + (1 - c->clc.stepX) / 2) / c->clc.ray_dir_x;
	else
		c->clc.perpWallDist = (c->clc.map_y - c->m->pos_x + (1 - c->clc.stepY) / 2) / c->clc.ray_dir_y;
	c->clc.lineHeight = (int)(c->win_height / c->clc.perpWallDist);
	c->clc.drawStart = (c->win_height / 2) - (c->clc.lineHeight / 2);
	if (c->clc.drawStart < 0)
		c->clc.drawStart = 0;
	c->clc.drawEnd = (c->clc.lineHeight / 2) + (c->win_height / 2);
	if (c->clc.drawEnd >= c->win_height)
		c->clc.drawEnd = c->win_height - 1;
}

void	clc_text(t_cub *c)
{
	if (c->clc.side == 0)
		c->clc.wallX = c->m->pos_x + c->clc.perpWallDist * c->clc.ray_dir_y;
	else
		c->clc.wallX = c->m->pos_y + c->clc.perpWallDist * c->clc.ray_dir_x;
	c->clc.wallX -= floor(c->clc.wallX);
	c->clc.texX = (int)(c->clc.wallX * (double)TEXTWIDTH);
	if (c->clc.side == 0 && c->clc.ray_dir_x > 0)
		c->clc.texX = TEXTWIDTH - c->clc.texX - 1;
	if (c->clc.side == 1 && c->clc.ray_dir_y < 0)
		c->clc.texX = TEXTWIDTH - c->clc.texX - 1;
	c->clc.step = 1.0 * TEXTHEIGHT / c->clc.lineHeight;
	c->clc.textPos = (c->clc.drawStart - c->win_height / 2 + c->clc.lineHeight / 2) * c->clc.step;
}

