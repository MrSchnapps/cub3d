/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:32:38 by judecuyp          #+#    #+#             */
/*   Updated: 2020/01/29 13:52:06 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static int		ft_memory1(unsigned int nb)
{
	int cmpt;

	cmpt = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		cmpt++;
	}
	return (cmpt);
}

static char		*ft_putnbr_char(unsigned int nb, char *tab_nbr, int cmpt_memory)
{
	char	*base;

	base = "0123456789";
	if (nb > 9)
		ft_putnbr_char(nb / 10, tab_nbr, cmpt_memory - 1);
	tab_nbr[cmpt_memory] = base[nb % 10];
	return (tab_nbr);
}

char			*ft_itoa_pf(int nbr, t_plist *s)
{
	int				cmpt_memory;
	char			*tab_nbr;
	unsigned int	nb;

	if (!(cmpt_memory = 0) && nbr == 0)
	{
		if (!(tab_nbr = ft_zero_pf(s)))
			return (NULL);
	}
	else
	{
		if ((nb = nbr) && nbr < 0)
		{
			nb = nbr * -1;
			cmpt_memory += 1;
		}
		cmpt_memory += ft_memory1(nb);
		if (!(tab_nbr = (char *)malloc((cmpt_memory + 1) * sizeof(char))))
			return (NULL);
		if (nbr < 0)
			tab_nbr[0] = '-';
		tab_nbr = ft_putnbr_char(nb, tab_nbr, cmpt_memory - 1);
		tab_nbr[cmpt_memory] = '\0';
	}
	return (tab_nbr);
}
