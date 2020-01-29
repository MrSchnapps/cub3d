#include "../includes/cubd.h"

int		get_infos(char *info)
{
	char **info_split;

	info_split = ft_split(info, " ");
}

int     ft_map(t_map *map, char *ac_map)
{
	int		fd;
	int 	i;
	int		ret;

	if ((fd = open(ac_map, O_RDONLY)) < 0)
		return (1);
	i = 0;
	while (i < NB_INFOS && ret > 0)
	{
		ret = get_next_line(fd, &line);

	}


	close(fd);
	return (0);
}