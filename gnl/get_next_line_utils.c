/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 18:14:04 by judecuyp          #+#    #+#             */
/*   Updated: 2019/11/14 19:19:00 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	unsigned int i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char		*ft_strchr(const char *s, int c)
{
	int i;

	i = 0;
	while (*s != c)
	{
		if (*s == 0)
			return (0);
		s++;
	}
	return ((char *)s);
}

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;

	i = 0;
	if (!s)
		return (NULL);
	if (!(str = malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	if (ft_strlen(s) > start)
	{
		while (i < len && s[start + i])
		{
			str[i] = s[start + i];
			i++;
		}
	}
	str[i] = '\0';
	return (str);
}

char		*ft_strdup(const char *s1)
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

char		*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	char	*ptr_str;
	int		i;

	i = ft_strlen(s1);
	if (!s2)
		return (NULL);
	if (!(str = (char *)malloc((ft_strlen(s1)
		+ ft_strlen(s2) + 1) * sizeof(char))))
		return (NULL);
	ptr_str = str;
	if (s1)
		while (*s1)
			*str++ = *s1++;
	while (*s2)
		*str++ = *s2++;
	*str = '\0';
	return (ptr_str);
}
