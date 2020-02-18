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

// TERMINER LE TRIAGE DES SPRITES !!!!!
void	sort_sprite(int *sprite_order, int *sprite_distance, int nb_sprites)
{
	int i;
	double tmp;



	while (i < nb_sprites - 1)
	{
		if (sprite_distance[i] > sprite_distance[i + 1])
		{

		}
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
		c->sprt.zbuffer[x] = c->clc.perpWallDist;
	}

	int i;

	i = 0;
	while (i < c->m->nb_sprites)
	{
		c->sprt.sprite_order[i] = i;
		c->sprt.sprite_distance[i] = ((c->m->pos_y - c->sprt.all_sprites[i].y) * (c->m->pos_y - c->sprt.all_sprites[i].x) + 
									(c->m->pos_x - c->sprt.all_sprites[i].x) * (c->m->pos_x - c->sprt.all_sprites[i].x));
		i++;
	}
	int b;
	b = 0;
	while (b < 7)
	{
		printf("Sprite dist [%d] ==> |%f|\n", b, c->sprt.sprite_distance[b]);
		b++;
	}
	//sort_sprite(s->sprt.sprite_order, s->sprite_distance, s->m->nb_sprites)
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	return (0);
}