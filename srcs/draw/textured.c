#include "cub3d.h"

int     draw_text_map(t_cub *c)
{
	//int w;
	//int h;
	//int id;
	int	x;
	int y;
	//int *tab_text[4];
	//int texNum;
	//int	buffer[c->win_height][c->win_width];	
	//int	*pix;

	/*w = 64;
	h = 64;*/
	/*c->wall_n = mlx_xpm_file_to_image(c->mlx_ptr, "../img/eagle.xpm", &w, &h);
	c->wall_s = mlx_xpm_file_to_image(c->mlx_ptr, "../img/mossy.xpm", &w, &h);
	c->wall_e = mlx_xpm_file_to_image(c->mlx_ptr, "../img/wood.xpm", &w, &h);
	c->wall_w = mlx_xpm_file_to_image(c->mlx_ptr, "../img/colorstone.xpm", &w, &h);*/

	/*tab_text[0] = (int *)mlx_get_data_addr(c->wall_n, &id, &id, &id);
	tab_text[1] = (int *)mlx_get_data_addr(c->wall_s, &id, &id, &id);
	tab_text[2] = (int *)mlx_get_data_addr(c->wall_e, &id, &id, &id);
	tab_text[3] = (int *)mlx_get_data_addr(c->wall_w, &id, &id, &id);*/
	//pix = (int *)mlx_get_data_addr(c->img_ptr, &id, &id, &id);
	c->clc.done = 1;
	x = -1;
	int i;
	int j;

	i = 0;
	while (i < c->win_height / 2)
	{
		j = 0;
		while(j < c->win_width)
		{
			c->pix[i * c->win_width + j] = CYAN;
			j++;
		}
		i++;
	}
	i = c->win_height / 2;
	while (i < c->win_height)
	{
		j = 0;
		while(j < c->win_width)
		{
			c->pix[i * c->win_width + j] = BRUN;
			j++;
		}
		i++;
	}
	while (++x < c->win_width)
	{
		c->clc.camera_x = 2 * x / (double)c->win_width - 1;
		c->clc.ray_dir_x = c->m->dx + c->m->px * c->clc.camera_x;
		c->clc.ray_dir_y = c->m->dy + c->m->py * c->clc.camera_x;

		c->clc.map_x = (int)c->m->pos_y;
		c->clc.map_y = (int)c->m->pos_x;

		//c->clc.deltaDistX = fabs(1 / c->clc.ray_dir_x);
		//c->clc.deltaDistY = fabs(1 / c->clc.ray_dir_y);

		c->clc.deltaDistX = (c->clc.ray_dir_x == 0) ? 0 : ((c->clc.ray_dir_x == 0) ? 1 : fabs(1 / c->clc.ray_dir_x));
	 	c->clc.deltaDistY = (c->clc.ray_dir_y == 0) ? 0 : ((c->clc.ray_dir_y == 0) ? 1 : fabs(1 / c->clc.ray_dir_y));

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
		
		//texturing calculations
		if (c->clc.side == 1)
			c->clc.textNum = 0;
		else if (c->clc.side == 0)
			c->clc.textNum = 1;
		
		//calculate value of wallX
		if (c->clc.side == 0)
			c->clc.wallX = c->m->pos_x + c->clc.perpWallDist * c->clc.ray_dir_y;
		else
			c->clc.wallX = c->m->pos_y + c->clc.perpWallDist * c->clc.ray_dir_x;
		c->clc.wallX -= floor(c->clc.wallX);

		//x coordinate on the texture
		c->clc.texX = (int)(c->clc.wallX * (double)TEXTWIDTH);
		if (c->clc.side == 0 && c->clc.ray_dir_x > 0)
			c->clc.texX = TEXTWIDTH - c->clc.texX - 1;
		if (c->clc.side == 1 && c->clc.ray_dir_y < 0)
			c->clc.texX = TEXTWIDTH - c->clc.texX - 1;
		
		c->clc.step = 1.0 * TEXTHEIGHT / c->clc.lineHeight;
		c->clc.textPos = (c->clc.drawStart - c->win_height / 2 + c->clc.lineHeight / 2) * c->clc.step;
		y = c->clc.drawStart;

		
		while (y < c->clc.drawEnd)
		{
			//printf("\nw y ==> %d\n", y);
			c->clc.texY = (int)c->clc.textPos & (TEXTHEIGHT - 1);
			c->clc.textPos += c->clc.step;
			c->clc.color = c->tab_text[c->clc.textNum][TEXTHEIGHT * c->clc.texY + c->clc.texX];
			c->pix[y * c->win_width + x] = c->clc.color;
			y++;
		}
	}
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	return (0);
}