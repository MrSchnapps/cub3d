#include "cub3d.h"

void test(t_cub *c)
{
	c->m->nb_sprites = 7;
	c->sprt.all_sprites = (t_csprt *)malloc(7 * sizeof(t_csprt));
	c->sprt.all_sprites[0].x = 5.5;
	c->sprt.all_sprites[0].y = 9.5;
	c->sprt.all_sprites[1].x = 4.5;
	c->sprt.all_sprites[1].y = 13.5;
	c->sprt.all_sprites[2].x = 5.5;
	c->sprt.all_sprites[2].y = 13.5;
	c->sprt.all_sprites[3].x = 6.5;
	c->sprt.all_sprites[3].y = 13.5;
	c->sprt.all_sprites[4].x = 4.5;
	c->sprt.all_sprites[4].y = 15.5;
	c->sprt.all_sprites[5].x = 5.5;
	c->sprt.all_sprites[5].y = 15.5;
	c->sprt.all_sprites[6].x = 6.5;
	c->sprt.all_sprites[6].y = 15.5;
}

void	draw_ceil_floor(t_cub *c)
{
	int i;
	int j;

	i = -1;
	while (++i < c->win_height / 2)
	{
		j = -1;
		while(++j < c->win_width)
			c->pix[i * c->win_width + j] = CYAN;
	}
	i = c->win_height / 2;
	while (i < c->win_height)
	{
		j = -1;
		while(++j < c->win_width)
			c->pix[i * c->win_width + j] = BRUN;
		i++;
	}
}

void	vert_line_text(t_cub *c, int x)
{
	int y;

	y = c->clc.drawStart;	
	while (y < c->clc.drawEnd)
	{
		c->clc.texY = (int)c->clc.textPos & (TEXTHEIGHT - 1);
		c->clc.textPos += c->clc.step;
		c->clc.color = c->tab_text[c->clc.text_num][TEXTHEIGHT * c->clc.texY + c->clc.texX];
		c->pix[y * c->win_width + x] = c->clc.color;
		y++;
	}
}

void    vert_line(t_cub *c, int x)
{
	int i;

	i = 0;
	c->pix[c->clc.drawStart * c->win_width + x] = 0;
	c->clc.drawStart++;
	while (c->clc.drawStart < c->clc.drawEnd)
	{
		if (c->bords == 1)
			c->pix[c->clc.drawStart * c->win_width + x] = 0;
        else if (c->clc.text_num == 0)
            c->pix[c->clc.drawStart * c->win_width + x] = GRIS;
        else if (c->clc.text_num == 1)
            c->pix[c->clc.drawStart * c->win_width + x] = POURPRE;
		else if (c->clc.text_num == 2)
			c->pix[c->clc.drawStart * c->win_width + x] = ORANGE_CLAIR;
		else if (c->clc.text_num == 3)
			c->pix[c->clc.drawStart * c->win_width + x] = GREEN;
		c->clc.drawStart++;
	}
	c->pix[c->clc.drawStart * c->win_width + x] = 0;
}

void	sort_sprite(int *sprite_order, double *sprite_distance, int nb_sprites)
{
	int 	i;
	int		is_sort;
	int		tmp_order;
	double	tmp_dist;

	is_sort = 0;
	while (!is_sort)
	{
		is_sort = 1;
		i = -1;
		while (++i < nb_sprites - 1)
			if (sprite_distance[i] < sprite_distance[i + 1])
			{
				tmp_dist = sprite_distance[i];
				tmp_order = sprite_order[i];
				sprite_distance[i] = sprite_distance[i + 1];
				sprite_order[i] = sprite_order[i + 1];
				sprite_distance[i + 1] = tmp_dist;
				sprite_order[i + 1] = tmp_order;
				is_sort = 0;
			}
	}
}

int     draw_map(t_cub *c)
{
	int		x;


	int y;
	int d;

	x = -1;
	draw_ceil_floor(c);
	while (++x < c->win_width)
	{
		set_inf_map(c, x);
		clc_side_dest(c);
		clc_dist_hit(c);
		clc_start_end(c);
		if (c->textures == 0)
			vert_line(c, x);
		else
		{
			clc_text(c);
			vert_line_text(c, x);
		}
		c->sprt.zbuffer[x] = c->clc.perpWallDist;
	}

	int i;
	
	i = 0;
	while (i < c->m->nb_sprites)
	{
		c->sprt.sprite_order[i] = i;
		c->sprt.sprite_distance[i] = (((double)c->m->pos_y - c->sprt.all_sprites[i].y) * ((double)c->m->pos_y - c->sprt.all_sprites[i].y) + 
									((double)c->m->pos_x - c->sprt.all_sprites[i].x) * ((double)c->m->pos_x - c->sprt.all_sprites[i].x));
		i++;
	}
	sort_sprite(c->sprt.sprite_order, c->sprt.sprite_distance, c->m->nb_sprites);
	i = 0;
	while (i < c->m->nb_sprites)
	{
		c->sprt.sprite_x = c->sprt.all_sprites[c->sprt.sprite_order[i]].y - c->m->pos_y;
		c->sprt.sprite_y = c->sprt.all_sprites[c->sprt.sprite_order[i]].x - c->m->pos_x;
		c->sprt.inv_det = 1.0 / (c->m->px * c->m->dy - c->m->dx * c->m->py);
		c->sprt.transform_x = c->sprt.inv_det * (c->m->dy * c->sprt.sprite_x - c->m->dx * c->sprt.sprite_y);
		c->sprt.transform_y = c->sprt.inv_det * (-c->m->py * c->sprt.sprite_x + c->m->px * c->sprt.sprite_y);
		c->sprt.screen_x = (int)((c->win_width / 2) * (1 + c->sprt.transform_x / c->sprt.transform_y));
		c->sprt.sprite_height = abs((int)(c->win_height / c->sprt.transform_y));
		c->sprt.draw_start_y = -c->sprt.sprite_height / 2 + c->win_height / 2;
		if (c->sprt.draw_start_y < 0)
			c->sprt.draw_start_y = 0;
		c->sprt.draw_end_y = c->sprt.sprite_height / 2 + c->win_height / 2;
		if (c->sprt.draw_end_y >= c->win_height)
			c->sprt.draw_end_y = c->win_height - 1;
		c->sprt.sprite_width = abs((int)(c->win_height / c->sprt.transform_y));
		c->sprt.draw_start_x = -c->sprt.sprite_width / 2 + c->sprt.screen_x;
		if (c->sprt.draw_start_x < 0)
			c->sprt.draw_start_x = 0;
		c->sprt.draw_end_x = c->sprt.sprite_width / 2 + c->sprt.screen_x;
		if (c->sprt.draw_end_x >=  c->win_width)
			c->sprt.draw_end_x = c->win_width - 1;
		c->sprt.stripe = c->sprt.draw_start_x;
		while (c->sprt.stripe < c->sprt.draw_end_x)
		{
			c->sprt.s_text_x = (int)(256 * (c->sprt.stripe - (-c->sprt.sprite_width / 2 + c->sprt.screen_x))
								* TEXTWIDTH / c->sprt.sprite_width) / 256; 
			if (c->sprt.transform_y > 0 && c->sprt.stripe > 0 && c->sprt.stripe < c->win_width
					&& c->sprt.transform_y < c->sprt.zbuffer[c->sprt.stripe])
			{
				y = c->sprt.draw_start_y;
				while (y < c->sprt.draw_end_y)
				{
					d = y * 256 - c->win_height * 128 + c->sprt.sprite_height * 128;
					c->sprt.s_text_y = ((d * TEXTHEIGHT) / c->sprt.sprite_height) / 256;
					c->sprt.color = c->addr_sprite[TEXTWIDTH * c->sprt.s_text_y + c->sprt.s_text_x];
					if ((c->sprt.color & 0x00FFFFFF) != 0)
						c->pix[y * c->win_width + c->sprt.stripe] = c->sprt.color;
					y++;
				}
			}
			c->sprt.stripe++;
		}
		i++;
	}
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	return (0);
}