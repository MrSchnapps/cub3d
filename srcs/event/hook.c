#include "cub3d.h"

int ft_key_event(int key, t_cub *s)
{
	if (key == ESC)
		ft_exit_esc(s);
	if (key == W || key == A || key == S || key == D || key == DROITE || key == GAUCHE)
		ft_move(key, s);
	if (key == 17)
	{
		if (s->textures == 0)
		{
			draw_text_map(s);
			s->textures = 1;
		}
		else if (s->textures == 1)
		{
			draw_map(s);
			s->textures = 0;
		}
	}
	else 
		printf("touch pressee: %d\n", key);
	return (1);
}