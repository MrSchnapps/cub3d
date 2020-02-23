#include "cub3d.h"

int ft_key_event(int key, t_cub *c)
{
	if (key == ESC)
		ft_exit(c, 0);
	else if (key == W || key == S)
		move_vert(key, c);
	else if (key == A || key == D)
		move_side(key, c);
	else if (key == RIGHT || key == LEFT)
		move_turn(key, c);
	else if (key == T)
	{
		if (c->textures == 0)
			c->textures = 1;
		else if (c->textures == 1)
			c->textures = 0;
		draw_map(c);
	}
	return (1);
}
