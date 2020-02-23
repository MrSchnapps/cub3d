/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:27:42 by judecuyp          #+#    #+#             */
/*   Updated: 2019/10/22 15:21:49 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list *road;
	t_list *temp;

	road = *lst;
	if (!road || !del)
		return ;
	while (road)
	{
		temp = road->next;
		(*del)(road->content);
		free(road);
		road = temp;
	}
	*lst = NULL;
}
