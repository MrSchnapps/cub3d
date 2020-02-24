/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_sprite.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:35:40 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 15:36:17 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	get_num_sprites(t_map *m)
{
	int	i;
	int	j;

	i = -1;
	while (m->m[++i])
	{
		j = -1;
		while (m->m[i][++j])
		{
			if (m->m[i][j] == '2')
				m->nb_sprites++;
		}
	}
}

int		allocate_tabs(t_cub *c, t_map *m)
{
	if ((!(c->sprt.zbuffer = (double *)malloc(c->win_w *
		sizeof(double))))
	|| (!(c->sprt.sprite_order = (int *)malloc(m->nb_sprites *
		sizeof(int))))
	|| (!(c->sprt.sprite_distance = (double *)malloc(m->nb_sprites *
		sizeof(double))))
	|| (!(c->sprt.asprt = (t_csprt *)malloc(m->nb_sprites *
		sizeof(t_csprt)))))
		return (0);
	return (1);
}

int		ft_get_sprites(t_map *m, t_cub *c)
{
	int	i;
	int	j;
	int	len;

	len = 0;
	get_num_sprites(m);
	if (m->nb_sprites > 0)
	{
		if (!allocate_tabs(c, m))
			return (11);
		i = -1;
		while (m->m[++i])
		{
			j = -1;
			while (m->m[i][++j])
				if (m->m[i][j] == '2')
				{
					c->sprt.asprt[len].y = i + 0.5;
					c->sprt.asprt[len].x = j + 0.5;
					len++;
				}
		}
	}
	return (0);
}
