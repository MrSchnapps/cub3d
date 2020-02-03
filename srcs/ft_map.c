/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:47:37 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/03 21:36:26 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubd.h"

int		parse_res(char **split, t_map *map)
{
	int i;

	i = -1;
	while (split[1][++i])
		if (split[1][i] < 48 || split[1][i] > 57)
			return (-1);
	i = -1;
	while (split[2][++i])
		if (split[2][i] < 48 || split[2][i] > 57)
			return (-1);
	if ((map->res_x = atoi(split[1])) > 2560)
		map->res_x = 2560;
	if ((map->res_y = atoi(split[1])) > 1440)
		map->res_y = 1440;
	return (1);
}


int		parse_infos(char *line, t_map *m)
{
	char	**split;
	int		i;

	i = 0;
	if (!line || !(split = ft_split(line, ' ')))
		return (-1);
	i = ft_tablen(split);
	if (i < 2 || i > 3)
		return (-1);
	if (!ft_strcmp(split[0], "R") && i == 3 && m->res_x == -1 && m->res_y == -1)
	{
		if (parse_res(split, m) < 0)
			return (free_infos(split, 8));
	}
	else if (!ft_strcmp(split[0], "NO") && !m->no && i == 2)
	{
		if (!(m->no = ft_strdup(split[1])))
			return (free_infos(split, 10));
	}
	else if (!ft_strcmp(split[0], "SO") && i == 2 && !m->so)
	{
		if (!(m->so = ft_strdup(split[1])))
			return (free_infos(split, 10));
	}
	else if (!ft_strcmp(split[0], "WE") && i == 2 && !m->we)
	{
		if (!(m->we = ft_strdup(split[1])))
			return (free_infos(split, 10));
	}
	else if (!ft_strcmp(split[0], "EA") && i == 2 && !m->ea)
	{
		if (!(m->ea = ft_strdup(split[1])))
			return (free_infos(split, 10));
	}
	else if (!ft_strcmp(split[0], "S") && i == 2 && !m->sprite)
	{
		if (!(m->sprite = ft_strdup(split[1])))
			return (free_infos(split, 10));
	}

	//modif
	/*else if (!ft_strcmp(split[0], "F") && i == 2 && m->floor == -1)
	{
		if (parse_color(split, m)
			return (free_infos(split, 10));
	}*/
	else
		return (free_infos(split, 7));
	return (free_infos(split, 0));
}

int		ft_map(t_map *map, char *ac_map)
{
	int		fd;
	int		i;
	int		ret;
	int		ret_infos;
	char	*line;

	line = NULL;
	if ((fd = open(ac_map, O_RDONLY)) < 0)
		return (1);
	i = -1;
	ret = 1;
	while (++i < NB_INFOS && ret > 0)
	{
		while ((!line || !ft_strcmp(line, "")) && ret > 0)
		{
			ft_free(&line, 0, 0);
			if ((ret = get_next_line(fd, &line)) < 0)
				return (ft_free(&line, 2, fd));
		}
		if ((ret_infos = parse_infos(line, map)))
			return (ft_free(&line, ret_infos, fd));
		ft_free(&line, 0, 0);
	}
	ret = (i == NB_INFOS) ? 0 : ret;
	return (ft_free(&line, ret, fd));
}
