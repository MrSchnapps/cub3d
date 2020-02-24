/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:17:51 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 16:24:22 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_ceil_floor(t_cub *c)
{
	int i;
	int j;

	i = -1;
	while (++i < c->win_h / 2)
	{
		j = -1;
		while (++j < c->win_w)
			c->pix[i * c->win_w + j] = c->m->ceil;
	}
	i = c->win_h / 2;
	while (i < c->win_h)
	{
		j = -1;
		while (++j < c->win_w)
			c->pix[i * c->win_w + j] = c->m->floor;
		i++;
	}
}

void	vert_line_text(t_cub *c, int x)
{
	int y;

	y = c->clc.d_start;
	while (y < c->clc.d_end)
	{
		c->clc.texy = (int)c->clc.text_pos & (TEXTHEIGHT - 1);
		c->clc.text_pos += c->clc.step;
		c->clc.color = c->t_text[c->clc.text_num][TEXTHEIGHT *
			c->clc.texy + c->clc.texx];
		c->pix[y * c->win_w + x] = c->clc.color;
		y++;
	}
}

void	vert_line(t_cub *c, int x)
{
	int i;

	i = 0;
	c->pix[c->clc.d_start * c->win_w + x] = 0;
	c->clc.d_start++;
	while (c->clc.d_start < c->clc.d_end)
	{
		if (c->bords == 1)
			c->pix[c->clc.d_start * c->win_w + x] = 0;
		else if (c->clc.text_num == 0)
			c->pix[c->clc.d_start * c->win_w + x] = GREY;
		else if (c->clc.text_num == 1)
			c->pix[c->clc.d_start * c->win_w + x] = DARK_RED;
		else if (c->clc.text_num == 2)
			c->pix[c->clc.d_start * c->win_w + x] = LIGHT_ORANGE;
		else if (c->clc.text_num == 3)
			c->pix[c->clc.d_start * c->win_w + x] = GREEN;
		c->clc.d_start++;
	}
	c->pix[c->clc.d_start * c->win_w + x] = 0;
}

void	draw_sprites(t_cub *c)
{
	int d;
	int y;

	while (c->sprt.stripe < c->sprt.draw_end_x)
	{
		c->sprt.tx = (int)(256 * (c->sprt.stripe - (-c->sprt.sprite_width
			/ 2 + c->sprt.screen_x)) * TEXTWIDTH / c->sprt.sprite_width) / 256;
		if (c->sprt.trsfm_y > 0 && c->sprt.stripe > 0 && c->sprt.stripe
			< c->win_w && c->sprt.trsfm_y < c->sprt.zbuffer[c->sprt.stripe])
		{
			y = c->sprt.draw_start_y;
			while (y < c->sprt.draw_end_y)
			{
				d = y * 256 - c->win_h * 128 + c->sprt.sprite_height * 128;
				c->sprt.ty = ((d * TEXTHEIGHT) / c->sprt.sprite_height) / 256;
				c->sprt.color = c->ad_sprt[TEXTWIDTH *
								c->sprt.ty + c->sprt.tx];
				if ((c->sprt.color & 0x00FFFFFF) != 0)
					c->pix[y * c->win_w + c->sprt.stripe] = c->sprt.color;
				y++;
			}
		}
		c->sprt.stripe++;
	}
}

int		draw_map(t_cub *c)
{
	int	x;

	x = -1;
	draw_ceil_floor(c);
	while (++x < c->win_w)
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
		(c->m->nb_sprites > 0) ? c->sprt.zbuffer[x] = c->clc.pwd : 0;
	}
	if (c->m->nb_sprites > 0)
		clc_sprites(c);
	if (c->save == 1)
		return (ft_bmp(c));
	mlx_put_image_to_window(c->mlx_ptr, c->win_ptr, c->img_ptr, 0, 0);
	return (0);
}
