#include "cub3d.h"

void    vertLine(int x, int drawStart, int drawEnd, t_cub *c, int side)
{
	int	*pix;
	int	id;
	int i;

	i = 0;
	pix = (int *)mlx_get_data_addr(c->img_ptr, &id, &id, &id);
	while (i < drawStart)
	{
		pix[i * c->win_width + x] = CYAN;
		i++;
	}
	pix[drawStart * c->win_width + x] = 0;
	drawStart++;
	while (drawStart < drawEnd - 1)
	{
        if (side == 0)
            pix[drawStart * c->win_width + x] = GRIS;
        else
            pix[drawStart * c->win_width + x] = POURPRE;
		drawStart++;
	}
	pix[drawEnd * c->win_width + x] = 0;
	drawEnd++;
	while (drawEnd < c->win_height)
	{
		pix[drawEnd * c->win_width + x] = BRUN;
		drawEnd++;
	}
}

int     draw_map(t_cub *c)
{
	int		x;

	//if (!(c->img_ptr = mlx_new_image(c->mlx_ptr, c->win_width, c->win_height)))
	//	exit(1);
	c->clc.done = 1;
	x = -1;
	while (++x < c->win_width)
	{
		c->clc.camera_x = 2 * x / (double)c->win_width - 1;
		c->clc.ray_dir_x = c->m->dx + c->m->px * c->clc.camera_x;
		c->clc.ray_dir_y = c->m->dy + c->m->py * c->clc.camera_x;

		c->clc.map_x = (int)c->m->pos_y;
		c->clc.map_y = (int)c->m->pos_x;

		c->clc.deltaDistX = fabs(1 / c->clc.ray_dir_x);
		c->clc.deltaDistY = fabs(1 / c->clc.ray_dir_y);
		//deltaDistX = (ray_dir_x == 0) ? 0 : ((ray_dir_x == 0) ? 1 : fabs(1 / ray_dir_x));
     	//deltaDistY = (ray_dir_y == 0) ? 0 : ((ray_dir_y == 0) ? 1 : fabs(1 / ray_dir_y));
		c->clc.hit = 0;
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
		while (c->clc.hit == 0)
		{
			if (c->clc.sideDistX < c->clc.sideDistY)
			{
				c->clc.sideDistX += c->clc.deltaDistX;
				c->clc.map_x += c->clc.stepX;
				c->clc.side = 0;
			}
			else
			{
				c->clc.sideDistY += c->clc.deltaDistY;
				c->clc.map_y += c->clc.stepY;
				c->clc.side = 1;
			}
			if (c->m->m[c->clc.map_x][c->clc.map_y] == '1') 
				c->clc.hit = 1;
		}
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
		vertLine(x, c->clc.drawStart, c->clc.drawEnd, c, c->clc.side);
	}
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	return (0);
}