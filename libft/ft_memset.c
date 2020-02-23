/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 17:06:40 by judecuyp          #+#    #+#             */
/*   Updated: 2019/10/15 18:16:17 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *b2;
	unsigned char c2;

	c2 = (unsigned char)c;
	b2 = (unsigned char *)b;
	while (len--)
	{
		*b2 = c2;
		b2++;
	}
	return (b);
}
