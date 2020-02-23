/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 14:53:54 by judecuyp          #+#    #+#             */
/*   Updated: 2019/10/10 14:34:59 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*str;
	char	*ptrstr;

	if (!(str = (char *)malloc((ft_strlen(s1) + 1) * sizeof(char))))
		return (0);
	ptrstr = str;
	while (*s1)
		*str++ = *s1++;
	*str = '\0';
	return (ptrstr);
}
