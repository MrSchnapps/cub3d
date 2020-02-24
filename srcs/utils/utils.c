/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 15:40:07 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/24 15:40:18 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		ft_strlen_c(char *str)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(char *s1, char *s2)
{
	int i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int		ft_atoi_c(char *nptr)
{
	int					sign;
	unsigned int		nb;

	sign = 1;
	while (*nptr == ' ' || (*nptr >= 9 && *nptr <= 13))
		nptr++;
	if (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	nb = 0;
	while (*nptr >= 48 && *nptr <= 57)
	{
		nb = (nb * 10) + *nptr - '0';
		nptr++;
	}
	return ((int)(nb * sign));
}

int		ft_tablen(char **str, int j)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	if (j == 1)
		while (str[i])
			i++;
	if (j == 2)
		while (str[i] && ft_strcmp(str[i], ""))
			i++;
	return (i);
}

char	*ft_strdup_c(char *s1)
{
	char	*str;
	char	*ptrstr;

	if (!(str = (char *)malloc((ft_strlen_c(s1) + 1) * sizeof(char))))
		return (NULL);
	ptrstr = str;
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (ptrstr);
}
