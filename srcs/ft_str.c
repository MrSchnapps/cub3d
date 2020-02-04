/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 20:03:20 by judecuyp          #+#    #+#             */
/*   Updated: 2020/02/04 21:44:15 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cubd.h"

char	*ft_strdup(char *s1)
{
	char	*str;
	char	*ptrstr;

	if (!(str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (NULL);
	ptrstr = str;
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (ptrstr);
}