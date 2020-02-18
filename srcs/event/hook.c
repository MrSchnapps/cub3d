#include "cub3d.h"

int ft_key_event(int key, t_cub *c)
{
	if (key == ESC)
		ft_exit_esc(c);
	else if (key == W || key == S)
		move_vert(key, c);
	else if (key == A || key == D)
		move_side(key, c);
	else if (key == DROITE || key == GAUCHE)
		move_turn(key, c);
	else if (key == T)
	{
		if (c->textures == 0)
			c->textures = 1;
		else if (c->textures == 1)
			c->textures = 0;
		draw_map(c);
	}
	else 
		printf("touch pressee: %d\n", key);
	return (1);
}