#include "cub3d.h"

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

void	draw_sprites(t_cub *c)
{
	int d;
	int y;

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
}

int     draw_map(t_cub *c)
{
	int		x;
	
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
		if (c->m->nb_sprites > 0)
			c->sprt.zbuffer[x] = c->clc.perpWallDist;
	}
	if (c->m->nb_sprites > 0)
		clc_sprites(c);
	if (c->save== 1)
	{// attention a modif
		ft_bmp(c);
		ft_exit(c, 0);
	}
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	return (0);
}