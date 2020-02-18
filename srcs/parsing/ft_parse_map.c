/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 15:42:05 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/18 12:35:30 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_line(t_map *m, int i, int j, int l)
{
	while ((j = 1) && ++i < m->m_w - 1)
	{
		if ((l = ft_strlen(m->m[i])) < 3 || l != m->m_h)
			return (15);
		if (m->m[i][0] != '1' || m->m[i][l - 1] != '1')
			return (14);
		while (j < l - 1)
		{
			if (m->m[i][j] == 'N' || m->m[i][j] == 'S' || m->m[i][j] == 'E' 
					|| m->m[i][j] == 'W')
			{
				if (!m->start)
					init_nsew(m, i, j);
				else
					return (16);
			}
			else if (m->m[i][j] < 48 || m->m[i][j] > 50)
				return (17);
			j++;
		}
	}
	return (0);
}

int		check_map(t_map *map)
{
	int	i;

	i = 0;
	if ((map->m_w = ft_tablen(map->m, 2)) < 3)
		return (13);
	if (ft_tablen(map->m, 1) != map->m_w)
		return (19);
	while (map->m[0][i])
		if (map->m[0][i++] != '1')
			return (14);
	if ((map->m_h = i) < 3)
		return (15);
	i = 0;
	while (map->m[map->m_w - 1][i])
		if (map->m[map->m_w -1][i++] != '1')
			return (14);
	if (i != map->m_h)
		return (15);
	if ((i = check_line(map, 0, 0, 0)))
		return (i);
	return ((map->start == 0) ? 18 : 0);
}

char	**ft_append(char **m, char *line)
{
	int		len;
	char	**t;
	int		i;
	
	i = 0;
	len = ft_tablen(m, 1) + 1;
	if (!(t = (char **)malloc((len + 1) * sizeof(char *))))
		return (NULL);
	while (i < len - 1)
	{
		t[i] = ft_strdup(m[i]);
		i++;
	}
	t[i] = ft_strdup(line);
	t[i + 1] = NULL;
	return (t);

}

int		add_map(char *line_un, t_map *map, int fd, int ret)
{
	char *line;
	char **tmp;
	
	line = NULL;
	tmp = map->m;
	if (!(map->m = ft_append(map->m, line_un)))
		return (f_i(tmp, 11));
	f_i(tmp, 0);
	while (ret > 0)
	{
		ft_free(&line, 0, 0);
		if ((ret = get_next_line(fd, &line)) < 0)
			return (ft_free(&line, 2, fd));
		tmp = map->m;
		if (!(map->m = ft_append(map->m, line)))
		{
			f_i(tmp, 0);
			return (ft_free(&line, 11, fd));
		}
		f_i(tmp, 0);
	}
	return (ft_free(&line, 0, 0));
}

int     parse_map(int fd, t_map *map)
{
	char	*line;
	int     ret;
	
	ret = 1;
	line = NULL;
	while (!line || (!ft_strcmp(line, "") && ret > 0))
	{
		ft_free(&line, 0, 0);
		if ((ret = get_next_line(fd, &line)) < 0)
			return (ft_free(&line, 2, fd));
	}
	if (ret == 0 && !ft_strcmp(line, ""))
		return (ft_free(&line, 12, fd));
	if ((ret = add_map(line, map, fd, ret)))
		return (ft_free(&line, ret, fd));
	if ((ret = check_map(map)))
		return (ft_free(&line, ret, fd));
	return (ft_free(&line, 0, fd));
}