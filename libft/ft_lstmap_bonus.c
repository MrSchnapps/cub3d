/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: judecuyp <judecuyp@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 18:53:26 by judecuyp          #+#    #+#             */
/*   Updated: 2019/10/22 13:42:34 by judecuyp         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *))
{
	t_list *road;
	t_list *new;
	t_list *temp;
	t_list *ptr_new;

	road = lst;
	if (road && (*f))
	{
		temp = NULL;
		new = ft_lstnew((*f)(road->content));
		ptr_new = new;
		road = road->next;
		while (road)
		{
			temp = ft_lstnew((*f)(road->content));
			new->next = temp;
			new = new->next;
			road = road->next;
		}
		return (ptr_new);
	}
	return (NULL);
}
