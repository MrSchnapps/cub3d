/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 17:46:24 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/03 19:03:29 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubd.h"

int     ft_free(char **str, int ret, int fd)
{
	if (str)
	{
		if (*str)
			free(*str);
		*str = NULL;
	}
	if (fd)
		close(fd);
	return (ret);
}

int		free_infos(char **str, int ret)
{
	int i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i])
				free(str[i]);
			i++;
		}
		free(str);
	}
	return (ret);
}