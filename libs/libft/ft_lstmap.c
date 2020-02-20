/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jchotel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 11:30:05 by jchotel           #+#    #+#             */
/*   Updated: 2019/11/09 15:09:44 by jchotel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *new;
	t_list *ref;

	if (!lst)
		return (0);
	if (!(new = ft_lstnew((*f)(lst->content))))
		return (0);
	ref = new;
	while (lst)
	{
		if (lst->next)
		{
			if (!(new->next = ft_lstnew((*f)(lst->next->content))))
			{
				ft_lstclear(&ref, del);
				return (0);
			}
			new = new->next;
		}
		lst = lst->next;
	}
	new->next = 0;
	return (ref);
}
