/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 19:47:37 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/07 14:25:35 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		parse_res(char **split, t_cub *c)
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
	if ((c->win_w = ft_atoi_c(split[1])) > 2560)
		c->win_w = 2560;
	if ((c->win_h = ft_atoi_c(split[2])) > 1440)
		c->win_h = 1440;
	return (1);
}

int		parse_color(char *str, int *nb)
{
	short	tab[3];
	int		i;
	int		j;
	
	i = 0;
	j = -1;
	while (++j < 3 && str[i])
	{
		tab[j] = ft_atoi_c(&str[i]);
		while (str[i] != ',' && str[i])
			if (str[i] < 48 || str[i++] > 57)
				return (-1);
		if (j < 2 && str[i++] == ',')
			if (str[i] == ',' && (i += 1))
				return (-1);
	}
	if (str[i] || j < 2 || tab[0] > 255 || tab[1] > 255 || tab[2] > 255)
		return (-1);
	*nb = (tab[0] * 256 * 256) + (tab[1] * 256) + tab[2];
	return (1);
}

int		parse_infos(char *line, t_map *m, t_cub *c)
{
	char	**s;
	int		i;

	if (!line || !(s = ft_split_c(line, ' ')))
		return (7);
	i = ft_tablen(s, 1);
	if (i < 2 || i > 3)
		return (7);
	if (!ft_strcmp(s[0], "R") && i == 3 && c->win_h == -1 && c->win_w == -1)
		return ((parse_res(s, c) < 0) ? f_i(s, 8) : f_i(s, 0));
	else if (!ft_strcmp(s[0], "NO") && i == 2 && !m->no)
		return ((!(m->no = ft_strdup_c(s[1]))) ? f_i(s, 11) : f_i(s, 0));
	else if (!ft_strcmp(s[0], "SO") && i == 2 && !m->so)
		return ((!(m->so = ft_strdup_c(s[1]))) ? f_i(s, 11) : f_i(s, 0));
	else if (!ft_strcmp(s[0], "WE") && i == 2 && !m->we)
		return ((!(m->we = ft_strdup_c(s[1]))) ? f_i(s, 11) : f_i(s, 0));
	else if (!ft_strcmp(s[0], "EA") && i == 2 && !m->ea)
		return ((!(m->ea = ft_strdup_c(s[1]))) ? f_i(s, 11) : f_i(s, 0));
	else if (!ft_strcmp(s[0], "S") && i == 2 && !m->sprite)
		return ((!(m->sprite = ft_strdup_c(s[1]))) ? f_i(s, 11) : f_i(s, 0));
	else if (!ft_strcmp(s[0], "F") && i == 2 && m->floor == -1)
		return ((parse_color(s[1], &m->floor) < 0) ? f_i(s, 9) : f_i(s, 0));
	else if (!ft_strcmp(s[0], "C") && i == 2 && m->ceil == -1)
		return ((parse_color(s[1], &m->ceil) < 0) ? f_i(s, 10) : f_i(s, 0));
	return (f_i(s, 7));
}

int		ft_read_map(int fd, t_map *map, t_cub *c)
{
	int		i;
	int		ret;
	int		ret_infos;
	char	*line;

	line = NULL;
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
		if ((ret_infos = parse_infos(line, map, c)))
			return (ft_free(&line, ret_infos, fd));
		ft_free(&line, 0, 0);
	}
	if (i !=  NB_INFOS)
		return (ft_free(&line, ret, fd));
	return (parse_map(fd, map));
}

int		ft_map(t_map *map, t_cub *c, char *ac_map)
{
	int fd;
	int	ret;

	if ((fd = open(ac_map, O_RDONLY)) < 0)
		return (1);
	ret = ft_read_map(fd, map, c);
	close(fd);
	return (ret);
}
