/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 12:38:54 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/05 17:00:42 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int		ft_check_char(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int		ft_string(char const *s, char c)
{
	int m;

	m = 0;
	if (!s)
		return (0);
	while (!ft_check_char(*s, c) && *s)
	{
		s++;
		m++;
	}
	return (m);
}

static int		ft_memory(char const *s, char c)
{
	int	m;

	m = 0;
	if (!s)
		return (0);
	while (ft_check_char((char)*s, c) && *s)
		s++;
	while (*s)
	{
		while (!ft_check_char((char)*s, c) && *s)
			s++;
		while (ft_check_char((char)*s, c) && *s)
			s++;
		m++;
	}
	return (m);
}

static void		ft_free_split(char **str, int j)
{
	while (j >= 0)
	{
		if (str[j])
			free(str[j]);
		j--;
	}
	free(str);
}

char			**ft_split_c(char *s, char c)
{
	char	**tab;
	int		i;
	int		j;

	if (!s || !(tab = (char **)malloc((ft_memory(s, c) + 1) * sizeof(char *))))
		return (0);
	while (ft_check_char(*s, c) && *s)
		s++;
	j = 0;
	while (*s && !(i = 0))
	{
		if (!(tab[j] = (char *)malloc((ft_string(s, c) + 1))))
		{
			ft_free_split(tab, j);
			return (0);
		}
		while (!ft_check_char((char)*s, c) && *s)
			tab[j][i++] = *s++;
		while (ft_check_char((char)*s, c) && *s)
			s++;
		tab[j][i] = '\0';
		j++;
	}
	tab[j] = NULL;
	return (tab);
}